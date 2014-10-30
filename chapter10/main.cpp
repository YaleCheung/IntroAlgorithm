//
//  main.cpp
//  cluster_from_the first_day
//
//  Created by zybjtu on 10/16/14.
//  Copyright (c) 2014 zybjtu. All rights reserved.
//

#include <iostream>
#include "lstfile.h"
#include "split.h"

#include <fstream>

#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <map>
#include <boost/bimap.hpp>
#include <bitset>

#include <vector>
#include <string>
using namespace std;
using namespace boost;

// time controlling to avoid magic num;
// the first term includes MIDDLE
// the second term excludes MIDDLE
#define EPISODENUM 50
#define MIDDLEEPISODE 26

#define SPLIT 111119
#define MIDDLE 1321632000 // middle stamp
#define STARTING 1320508800  // unix stamp
#define ENDING 1322755200 // ending stamp

// Some Typedefs.
typedef string FileName;
typedef string DirName;
typedef string Input;
typedef string Output;
typedef string Uid;
typedef string EpisodeId;
typedef int EpisodeIdx;
typedef int Time;
typedef int Duration;
typedef int BeginTime;
typedef int UnixStamp;
typedef int Day;

typedef map<Uid, map<Time, map<EpisodeIdx, Duration>>> UidWatchInfo;
typedef map<EpisodeId, EpisodeIdx> EpisodeInfo;
typedef map<int, int> DayReleaseDay;
typedef map<string,vector<int>> UidFeature;
typedef map<Uid, int> UidBeginTime;
typedef map<Day, UnixStamp> DayTimeStamp;
typedef bimap<Day, int> ReleasedayCount;
typedef map<Uid, bitset<EPISODENUM + 1>> UidEpisodeWatchBool;
// features:
// 1. the duration of the last watch and now.
// 2. how many episodes not watched.
// 3. the valid watch day
// 4. the total number of episodes watched.

// unix stamp to string.

Input episode_file = "/Users/zhangyi/Documents/work/Data/channel_id/10032441_sort.xml";
Input release_day_file = "/Users/zhangyi/Documents/work/Data/workspace/result/stastic/episode_add_into_system/10032441";
DirName data_path = "/Users/zhangyi/Documents/work/Data/four_dif_series/100324411/";
Output feature_file = "/Users/zhangyi/Documents/work/ClusteringToUserModes/feature_data/10032441";

int strtotime(const char* datetime)
{
    struct tm tm_time;
    int unixtime;
    strptime(datetime, "%Y-%m-%d %H:%M:%S", &tm_time);

    unixtime = mktime(&tm_time);
    return unixtime;
}

inline string time_resolve(const int& unix_time) {
    time_t timer(unix_time);
    tm* t = localtime(&timer);
    int year = t->tm_year + 1900;
    int month = t->tm_mon + 1;
    int day = t->tm_mday;
    
    //int year_2w = year % 100;
    
    char date[512];
    sprintf(date, "%04d-%02d-%02d %02d:%02d:%02d", year, month, day, 0, 0, 0);
    string tmp(date);
    return tmp;
}

/*void Day2UnixStamp(DayTimeStamp& day_time_stamp) {
    int unix_time = STARTING;
    
    while(1) {
        if(unix_time < ENDING) {
            int day = atoi(time_resolve(unix_time).c_str());
            day_time_stamp.insert(DayTimeStamp::value_type(day, unix_time));
            unix_time += 86400;
        } else
            break;
    }
}*/

void DayTime2ReleaseTime(const Input& release_time_file, DayReleaseDay& day_releaseday, ReleasedayCount& release_day_count) {
    ifstream release_fin(release_time_file.c_str(), ios::in);
    string line;
    int start = STARTING;
    int end = ENDING;
    set<int> release_day;
    // read release day
    while(getline(release_fin, line)) {
        vector<string> fields;
        str_split(line, fields);
        int release_time = atoi(fields[2].c_str());
        release_day.insert(release_time);
    }
    // read the release day
    int i = 0;
    for(auto iter = release_day.begin(); iter != release_day.end();iter ++) {
        int day = *iter;
        release_day_count.insert(ReleasedayCount::value_type(day, i));
        i ++;
        
        cout << i << '\t' << release_day_count.left.rbegin()->first << '\t' << release_day_count.left.rbegin()->second << endl;
        
    }
    
    release_fin.close();
    // make day into release_day
    while(start <= end) {
        int day = start;
        if(! release_day.count(start)) {
            int release_day_predict1 = (start - 3600 * 24);
            int release_day_predict2 = (start - 3600 * 24 * 2);
            int release_day_predict3 = (start - 3600 * 24 * 3);
            int release_day_predict4 = (start - 3600 * 24 * 4);
            if(release_day.count(release_day_predict1))
                day = release_day_predict1;
            else if(release_day.count(release_day_predict2))
                day = release_day_predict2;
            else if(release_day.count(release_day_predict3))
                day = release_day_predict3;
            else if(release_day.count(release_day_predict4))
                day = release_day_predict4;
            else
                cout << "not enough" << start << endl;
        }
        day_releaseday[start] = day;
        start += 3600 * 24;
    }
    cout << "read release day complete" << endl;
}

void ReadEpisodeInfo(const FileName& episode_file, EpisodeInfo& episode_info) {
    ifstream fin(episode_file.c_str(), ios::in);
    string line;
    
    while(getline(fin, line)){
        vector<string> fields;
        str_split(line, fields);
        
        string episode_id = fields[0];
        int episode_idx = atoi(fields[1].c_str());
        
        episode_info[episode_id] = episode_idx;
    }
    fin.close();
    cout << "Read Episode Info Finish!" << endl;
}


void ReadWatchInfo(const DirName& dir_path, const EpisodeInfo& episode_info, const DayReleaseDay& day_releaseday, UidWatchInfo& uid_watch_info, UidBeginTime& uid_begin_time, const DayTimeStamp& day_time_stamp, UidEpisodeWatchBool& uid_episode_watch_bool) {
    // list files
    vector<FileName> filenames;
    list_filenames(dir_path, filenames);
    // read filein;
    // a uid watch a episode multiple times;
    int repeat_num = 0;
    for(auto file : filenames) {
        ifstream fin_info(file.c_str(), ios::in);
        string line;
        cout << "reading from file: " << file << endl;
        int i = 0;
        int line_order = 0;
        while (getline(fin_info, line)) {
            i ++;
            if(i % 100000 == 0)
                cout << "line: " << i << endl;
            

            vector<string> fields;
            str_split(line, fields);
            Uid uid = fields[0];
            string iid = fields[1];
            int watchtime = atoi(fields[2].c_str());
            int endtime = atoi(fields[3].c_str());
            int starttime = (endtime - watchtime);
            if (watchtime < 300)
                continue;
            if(starttime > ENDING)
                continue;
            if(starttime < STARTING)
                continue;
            // time resolve error
            //int day = (starttime) / 86400 * 86400 -8 * 3600 +  86400;
            string day_time = time_resolve(starttime);
            int day = strtotime(day_time.c_str());
            //if(line_order % 100000 == 0)
             //   cout << "yuanben" << day_time << "    unix_init" << day << endl;
            line_order += 1;
            int release_day = day_releaseday.at(day);
            
            // cal begin time of each user access into the system.
            if(uid_begin_time.count(uid)) {
                int begin_time = uid_begin_time[uid];
                if(release_day < begin_time) {
                    uid_begin_time[uid] = release_day;
                }
            } else
                uid_begin_time[uid] = release_day;
            // judge whether the episode has been watched.
            int iidx = episode_info.at(iid);
            if(uid_episode_watch_bool.count(uid)) {
                if(uid_episode_watch_bool[uid].test(iidx))
                    continue;
            } else {
                uid_episode_watch_bool[uid] = bitset<EPISODENUM + 1>();
                uid_episode_watch_bool[uid].set(iidx);
            }
            uid_watch_info[uid][release_day][iidx] = watchtime;
        }
        fin_info.close();
    }
    cout << "Read Watch Info Finish!" << endl;
    cout << "But there are " << repeat_num << " repeate watching"<< endl;
    return;
}


void cal_features(const UidWatchInfo& uid_watch_info, UidFeature& uid_come_or_not, UidFeature& uid_watch_times, const ReleasedayCount& release_day_count) {
    int release_day_num = int(release_day_count.size());
    for(auto iter = uid_watch_info.begin(); iter != uid_watch_info.end(); iter ++) {
        string uid = iter -> first;
        for(auto iter2= iter->second.begin(); iter2 != iter->second.end(); iter2 ++) {
            int watch_time = iter2 -> first;
            int watch_num = int(iter2->second.size());
            int order = release_day_count.left.at(watch_time);
            if(! uid_come_or_not.count(uid))
                uid_come_or_not[uid] = std::move(vector<int>(release_day_num + 1, 0));
            uid_come_or_not[uid][order] = 1;
            // uid_watch_times
            if(uid_watch_times.count(uid))
                uid_watch_times[uid] = std::move(vector<int>(release_day_num + 1, 0));
            uid_watch_times[uid][order] += watch_num;
        }
    }
}

// output the feature by the day uid comes;
void output(const DirName& watch_times_dirname, const DirName& watch_bool_dirname, const UidFeature& uid_watch_or_not, const UidFeature& uid_watch_times, const UidBeginTime& uid_beg_time, const ReleasedayCount& releaseday_count) {
    int releaseday_size = int(releaseday_count.size());
    ofstream* p_watch_times_fouts = new ofstream[releaseday_size + 1];
    ofstream* p_watch_bool_fouts = new ofstream[releaseday_size + 1];
    for(auto i = 0; i < releaseday_size; i ++) {
        char filename[100] = {0};
        sprintf(filename, "%s%d",watch_times_dirname.c_str(), i);
        p_watch_times_fouts[i].open(filename, ios::out);
    }
    
    for(auto i = 0; i < releaseday_size; i ++) {
        char filename[100] = {0};
        sprintf(filename, "%s%d",watch_bool_dirname.c_str(), i);
        p_watch_bool_fouts[i].open(filename, ios::out);
    }
    
    for(auto iter = uid_watch_times.begin(); iter != uid_watch_times.end(); iter ++) {
        string uid = iter -> first;
        int begin_time = uid_beg_time.at(uid);
        int order = releaseday_count.left.at(begin_time);
        p_watch_times_fouts[order] << uid << " ";
        p_watch_bool_fouts[order] << uid << " ";
        for(int i = order; i < releaseday_size - 1; i ++) {
            p_watch_times_fouts[order] << uid_watch_times.at(uid).at(i) << " ";
            p_watch_bool_fouts[order] << uid_watch_or_not.at(uid).at(i) << " ";
        }
        p_watch_times_fouts[order] << uid_watch_times.at(uid).at(releaseday_size - 1) << endl;
        p_watch_bool_fouts[order] << uid_watch_or_not.at(uid).at(releaseday_size - 1) << endl;
    }
    delete [] p_watch_bool_fouts;
    delete [] p_watch_times_fouts;
}

int main(int argc, const char * argv[]) {
    DirName watch_times_dirname = "/Users/zhangyi/Documents/work/cluster_from_the_first_day/watch_times_data/";
    DirName watch_bool_dirname = "/Users/zhangyi/Documents/work/cluster_from_the_first_day/watch_bool_data/";
    UidFeature uid_watch_bool;
    UidFeature uid_watch_times;
    UidBeginTime uid_beg_time;
    ReleasedayCount releaseday_count;
    UidWatchInfo  uid_watch_info;
    EpisodeInfo episode_info;
    DayReleaseDay day_releaseday;
    DayTimeStamp day_timestamp;
    UidEpisodeWatchBool uid_episode_watch_bool;
    
    DayTime2ReleaseTime(release_day_file, day_releaseday, releaseday_count);
    ReadEpisodeInfo(episode_file, episode_info);
    ReadWatchInfo(data_path, episode_info, day_releaseday, uid_watch_info, uid_beg_time, day_timestamp, uid_episode_watch_bool);
    cal_features(uid_watch_info, uid_watch_bool, uid_watch_times, releaseday_count);
    cout <<" cal_features comp" << endl;

    cout << "output begin" << endl;
    output(watch_times_dirname, watch_bool_dirname, uid_watch_bool, uid_watch_times, uid_beg_time, releaseday_count);
    
    // output;
    
    return 0;
}
