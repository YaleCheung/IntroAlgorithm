#!/bin/python

from sklearn.cross_validation import cross_val_score
from sklearn.datasets import make_blobs
from sklearn.ensemble import RandomForestClassifier
from sklearn.ensemble import ExtraTreesClassifier
from sklearn.tree import DecisionTreeClassifier
from sklearn.cross_validation import train_test_split

import numpy as np
import random

feature_num = 10
clust_order = 2
data_dir_pat = "/Users/zhangyi/Documents/work/cluster_for_new_users/data_cluster_result/%dtimes_%d"
# obtain the size of users;
# consist the cluster
clust_population_dir = "/Users/zhangyi/Documents/work/cluster_for_new_users/stastic/cluster_pupulation/%d_file_2_clust"

def LoadPopulationDir():
    id_clust_info = {}
    for i in range(0, 20):
        clust_population_path = clust_population_dir % i
        fin = open(clust_population_path, 'r')
        for line in fin:
            fields = line.rstrip().split(' ')
            clust_order = int(fields[0])
            clust_num = int(fields[1])
            id_clust_info.setdefault(i, {})
            id_clust_info[i][clust_order] = clust_num
        fin.close()
    return id_clust_info

def DataSetInit():
    line_num = 0
    for file_order in range(0, 15):
        data_path = data_dir_pat % (file_order, clust_order)
        fin = open(data_path, 'r')
        line_order = 0
        for line in fin:
            line_order += 1
        line_num += line_order
	fin.close()
    # 0 col is the label
    print("data_volumn: " + str(line_num))
    dataset = np.zeros((line_num, feature_num + 1))
    return dataset

# load data set
def LoadData(data_set, id_clust_info):
    line_order = 0
    for file_order in range(0, 15):
        data_path = data_dir_pat % (file_order, clust_order)
        features = np.loadtxt(data_path)

	# generate sub features
	(rows, cols) = np.shape(features)
        print("rows %d cols %d" % (rows, cols))
	sub_features = features[:, 0:(feature_num + 1)]
        # fix the clust to keep insistence of sub_features
        # inverse the first col
        if id_clust_info[file_order][1] > id_clust_info[file_order][0]:
            print("inverse %d" % file_order)
            (sub_rows, sub_cols) = np.shape(sub_features)
            for i in range(sub_rows):
                sub_features[i, 0] = 1 - sub_features[i, 0]

	# copy data to dataset
	for i in range(rows):
	    for j in range(feature_num + 1):
                dataset[line_order + i, j] = sub_features[i, j]
        
        line_order += rows
    return data_set
# generate label
def Labels(data_set):
    return data_set[:, 0]
# TrainningSet testset
def Features(data_set):
    """ return features from dataset """
    return data_set[:, 1:]

def RandomSliceDataSet(dataset, train_prob = 0.8):
    (rows, cols) = np.shape(dataset)
    train_num = dataset * 0.8
    test_num = rows - train_num
    total_order = 0
    train_order = 0
    test_order = 0
    test_set = np.zeros(test_num, cols - 1)
    train_set = np.zeros(train_num, cols - 1)
    test_label = np.zeros(test_num, 1)
    train_label = np.zeros(train_num, 1)
    # random generate dataset
    for i in range(rows):
        rd = random.random()
	if rd >= 0.8 and test_order <= test_num:
            # belong to test
            for j in range(cols - 1):
	        test_set[test_order, j + 1] = dataset[total_order, j + 1]
            test_label[test_order, 0] = dataset[total_order, 0]
            test_order += 1
	    total_order += 1
        elif train_order <= train_num:
            # belong to trainning set
            for j in range(cols - 1):
	        train_set[train_order, j + 1] = dataset[total_order, j + 1]
            train_label[train_order, 0] = dataset[total_order, 0]
            train_order += 1
	    total_order += 1
        elif test_order > test_num:
            # belong to train_set
            for j in range(cols - 1):
	        train_set[train_order, j + 1] = dataset[total_order, j + 1]
            train_label[train_order, 0] = dataset[total_order, 0] 
	    train_order += 1
	    total_order += 1
        elif train_order > train_num:
            for j in range(cols - 1):
                test_set[test_order, j + 1] = dataset[total_order, j + 1]
            test_label[test_order, 0] = dataset[total_order, 0]
            test_order += 1 
	    total_order += 1
    return (train_set, test_set, train_label, test_label)

def RF(train_set, train_label, test_set, test_label):
    # trainning
    clf = RandomForestClassifier(n_estimators = 10, max_depth = None, min_samples_split = 1, random_state = 0, n_jobs = 5)
    clf.fit(train_set, train_label)
    score = clf.score(test_set, test_label)
    test_label_predict = clf.predict(test_set)
    tt,tf,ff,ft = cal_recall(test_label, test_label_predict)
    # precision
    return (score, tt, tf, ff, ft)
def cal_recall(label_true, label_predict):
    """ tt tf ff ft precentage"""
    print label_predict
    rows_l, = np.shape(label_true)
    rows_r, = np.shape(label_predict)
    assert(rows_l == rows_r)
    true_num = 0
    false_num = 0
    tt_num = 0
    tf_num = 0
    ft_num = 0
    ff_num = 0
    for i in range(rows_l):
        if label_true[i] == 1:
            true_num += 1
            if label_true[i] == label_predict[i]:
                tt_num += 1
            else:
                tf_num += 1
        if label_true[i] == 0:
            false_num += 1
            if label_true[i] == label_predict[i]:
                ff_num += 1
            else:
                ft_num += 1
    print("t_num %d f_num %d" % (true_num, false_num))
    return (float(tt_num) / true_num, float(tf_num) / true_num, float(ff_num) / false_num, float(ft_num) / false_num)
    # false example predicted as false
if __name__ == "__main__":
    fout = open("precision.txt", 'w')
    dataset = DataSetInit()
    id_clust_info = LoadPopulationDir()
    LoadData(dataset, id_clust_info)
    features = Features(dataset)
    labels = Labels(dataset)
    print ("feature row %d col %d" % np.shape(features))
    print ("label row %d " %  np.shape(labels))
    # for cross validation
    for j in range(10):
        feature_train, feature_test, label_train, label_test = train_test_split(features, labels, test_size = 0.3, random_state = 42)
        print("feature_train shape: row %d col %d" % (np.shape(feature_train)[0], np.shape(feature_train)[1])) 
        print("feature_test shape: row:%d col:%d" % (np.shape(feature_test)[0], np.shape(feature_test)[1]))
        print("feature_train shape: row %d" % (np.shape(label_train)[0]))
        print("feature_train shape: row %d" % (np.shape(label_test)[0]))
        for i in range(2, 10):
            subtrains = feature_train[:, 0:i]
            subtests = feature_test[:, 0:i]
            (scores, tt, tf, ff, ft) = RF(subtrains, label_train,  subtests, label_test)
            fout.writelines(str(j) + " " + str(i) + " " + str(scores) + " " + str(tt) + " " + str(tf) + " " + str(ff) + " " + str(ft) + '\n')
    fout.close()
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
    return (float(tt_num) / true_num, float(tf_num) / true_num, float(ff_num) / false_num, float(ft_num) / false_num)
    return (float(tt_num) / true_num, float(tf_num) / true_num, float(ff_num) / false_num, float(ft_num) / false_num)
    return (float(tt_num) / true_num, float(tf_num) / true_num, float(ff_num) / false_num, float(ft_num) / false_num)
    return (float(tt_num) / true_num, float(tf_num) / true_num, float(ff_num) / false_num, float(ft_num) / false_num)
    return (float(tt_num) / true_num, float(tf_num) / true_num, float(ff_num) / false_num, float(ft_num) / false_num)
    return (float(tt_num) / true_num, float(tf_num) / true_num, float(ff_num) / false_num, float(ft_num) / false_num)
    return (float(tt_num) / true_num, float(tf_num) / true_num, float(ff_num) / false_num, float(ft_num) / false_num)
    return (float(tt_num) / true_num, float(tf_num) / true_num, float(ff_num) / false_num, float(ft_num) / false_num)
    return (float(tt_num) / true_num, float(tf_num) / true_num, float(ff_num) / false_num, float(ft_num) / false_num)
    return (float(tt_num) / true_num, float(tf_num) / true_num, float(ff_num) / false_num, float(ft_num) / false_num)
    return (float(tt_num) / true_num, float(tf_num) / true_num, float(ff_num) / false_num, float(ft_num) / false_num)
    return (float(tt_num) / true_num, float(tf_num) / true_num, float(ff_num) / false_num, float(ft_num) / false_num)
    return (float(tt_num) / true_num, float(tf_num) / true_num, float(ff_num) / false_num, float(ft_num) / false_num)
    # false example predicted as false
if __name__ == "__main__":
    fout = open("precision.txt", 'w')
    dataset = DataSetInit()
    id_clust_info = LoadPopulationDir()
    LoadData(dataset, id_clust_info)
    features = Features(dataset)
    labels = Labels(dataset)
    print ("feature row %d col %d" % np.shape(features))
    print ("label row %d " %  np.shape(labels))
    # for cross validation
    for j in range(10):
        feature_train, feature_test, label_train, label_test = train_test_split(features, labels, test_size = 0.3, random_state = 42)
        print("feature_train shape: row %d col %d" % (np.shape(feature_train)[0], np.shape(feature_train)[1])) 
        print("feature_test shape: row:%d col:%d" % (np.shape(feature_test)[0], np.shape(feature_test)[1]))
        print("feature_train shape: row %d" % (np.shape(label_train)[0]))
        print("feature_train shape: row %d" % (np.shape(label_test)[0]))
        for i in range(2, 10):
            subtrains = feature_train[:, 0:i]
            subtests = feature_test[:, 0:i]
            (scores, tt, tf, ff, ft) = RF(subtrains, label_train,  subtests, label_test)
            fout.writelines(str(j) + " " + str(i) + " " + str(scores) + " " + str(tt) + " " + str(tf) + " " + str(ff) + " " + str(ft) + '\n')
    fout.close()
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
    # false example predicted as false
if __name__ == "__main__":
    fout = open("precision.txt", 'w')
    dataset = DataSetInit()
    id_clust_info = LoadPopulationDir()
    LoadData(dataset, id_clust_info)
    features = Features(dataset)
    labels = Labels(dataset)
    print ("feature row %d col %d" % np.shape(features))
    print ("label row %d " %  np.shape(labels))
    # for cross validation
    for j in range(10):
        feature_train, feature_test, label_train, label_test = train_test_split(features, labels, test_size = 0.3, random_state = 42)
        print("feature_train shape: row %d col %d" % (np.shape(feature_train)[0], np.shape(feature_train)[1])) 
        print("feature_test shape: row:%d col:%d" % (np.shape(feature_test)[0], np.shape(feature_test)[1]))
        print("feature_train shape: row %d" % (np.shape(label_train)[0]))
        print("feature_train shape: row %d" % (np.shape(label_test)[0]))
        for i in range(2, 10):
            subtrains = feature_train[:, 0:i]
            subtests = feature_test[:, 0:i]
            (scores, tt, tf, ff, ft) = RF(subtrains, label_train,  subtests, label_test)
            fout.writelines(str(j) + " " + str(i) + " " + str(scores) + " " + str(tt) + " " + str(tf) + " " + str(ff) + " " + str(ft) + '\n')
    fout.close()
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
    # false example predicted as false
if __name__ == "__main__":
    fout = open("precision.txt", 'w')
    dataset = DataSetInit()
    id_clust_info = LoadPopulationDir()
    LoadData(dataset, id_clust_info)
    features = Features(dataset)
    labels = Labels(dataset)
    print ("feature row %d col %d" % np.shape(features))
    print ("label row %d " %  np.shape(labels))
    # for cross validation
    for j in range(10):
        feature_train, feature_test, label_train, label_test = train_test_split(features, labels, test_size = 0.3, random_state = 42)
        print("feature_train shape: row %d col %d" % (np.shape(feature_train)[0], np.shape(feature_train)[1])) 
        print("feature_test shape: row:%d col:%d" % (np.shape(feature_test)[0], np.shape(feature_test)[1]))
        print("feature_train shape: row %d" % (np.shape(label_train)[0]))
        print("feature_train shape: row %d" % (np.shape(label_test)[0]))
        for i in range(2, 10):
            subtrains = feature_train[:, 0:i]
            subtests = feature_test[:, 0:i]
            (scores, tt, tf, ff, ft) = RF(subtrains, label_train,  subtests, label_test)
            fout.writelines(str(j) + " " + str(i) + " " + str(scores) + " " + str(tt) + " " + str(tf) + " " + str(ff) + " " + str(ft) + '\n')
    fout.close()
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
    # false example predicted as false
if __name__ == "__main__":
    fout = open("precision.txt", 'w')
    dataset = DataSetInit()
    id_clust_info = LoadPopulationDir()
    LoadData(dataset, id_clust_info)
    features = Features(dataset)
    labels = Labels(dataset)
    print ("feature row %d col %d" % np.shape(features))
    print ("label row %d " %  np.shape(labels))
    # for cross validation
    for j in range(10):
        feature_train, feature_test, label_train, label_test = train_test_split(features, labels, test_size = 0.3, random_state = 42)
        print("feature_train shape: row %d col %d" % (np.shape(feature_train)[0], np.shape(feature_train)[1])) 
        print("feature_test shape: row:%d col:%d" % (np.shape(feature_test)[0], np.shape(feature_test)[1]))
        print("feature_train shape: row %d" % (np.shape(label_train)[0]))
        print("feature_train shape: row %d" % (np.shape(label_test)[0]))
        for i in range(2, 10):
            subtrains = feature_train[:, 0:i]
            subtests = feature_test[:, 0:i]
            (scores, tt, tf, ff, ft) = RF(subtrains, label_train,  subtests, label_test)
            fout.writelines(str(j) + " " + str(i) + " " + str(scores) + " " + str(tt) + " " + str(tf) + " " + str(ff) + " " + str(ft) + '\n')
    fout.close()
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
    # false example predicted as false
if __name__ == "__main__":
    fout = open("precision.txt", 'w')
    dataset = DataSetInit()
    id_clust_info = LoadPopulationDir()
    LoadData(dataset, id_clust_info)
    features = Features(dataset)
    labels = Labels(dataset)
    print ("feature row %d col %d" % np.shape(features))
    print ("label row %d " %  np.shape(labels))
    # for cross validation
    for j in range(10):
        feature_train, feature_test, label_train, label_test = train_test_split(features, labels, test_size = 0.3, random_state = 42)
        print("feature_train shape: row %d col %d" % (np.shape(feature_train)[0], np.shape(feature_train)[1])) 
        print("feature_test shape: row:%d col:%d" % (np.shape(feature_test)[0], np.shape(feature_test)[1]))
        print("feature_train shape: row %d" % (np.shape(label_train)[0]))
        print("feature_train shape: row %d" % (np.shape(label_test)[0]))
        for i in range(2, 10):
            subtrains = feature_train[:, 0:i]
            subtests = feature_test[:, 0:i]
            (scores, tt, tf, ff, ft) = RF(subtrains, label_train,  subtests, label_test)
            fout.writelines(str(j) + " " + str(i) + " " + str(scores) + " " + str(tt) + " " + str(tf) + " " + str(ff) + " " + str(ft) + '\n')
    fout.close()
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
    # false example predicted as false
if __name__ == "__main__":
    fout = open("precision.txt", 'w')
    dataset = DataSetInit()
    id_clust_info = LoadPopulationDir()
    LoadData(dataset, id_clust_info)
    features = Features(dataset)
    labels = Labels(dataset)
    print ("feature row %d col %d" % np.shape(features))
    print ("label row %d " %  np.shape(labels))
    # for cross validation
    for j in range(10):
        feature_train, feature_test, label_train, label_test = train_test_split(features, labels, test_size = 0.3, random_state = 42)
        print("feature_train shape: row %d col %d" % (np.shape(feature_train)[0], np.shape(feature_train)[1])) 
        print("feature_test shape: row:%d col:%d" % (np.shape(feature_test)[0], np.shape(feature_test)[1]))
        print("feature_train shape: row %d" % (np.shape(label_train)[0]))
        print("feature_train shape: row %d" % (np.shape(label_test)[0]))
        for i in range(2, 10):
            subtrains = feature_train[:, 0:i]
            subtests = feature_test[:, 0:i]
            (scores, tt, tf, ff, ft) = RF(subtrains, label_train,  subtests, label_test)
            fout.writelines(str(j) + " " + str(i) + " " + str(scores) + " " + str(tt) + " " + str(tf) + " " + str(ff) + " " + str(ft) + '\n')
    fout.close()
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
    # false example predicted as false
if __name__ == "__main__":
    fout = open("precision.txt", 'w')
    dataset = DataSetInit()
    id_clust_info = LoadPopulationDir()
    LoadData(dataset, id_clust_info)
    features = Features(dataset)
    labels = Labels(dataset)
    print ("feature row %d col %d" % np.shape(features))
    print ("label row %d " %  np.shape(labels))
    # for cross validation
    for j in range(10):
        feature_train, feature_test, label_train, label_test = train_test_split(features, labels, test_size = 0.3, random_state = 42)
        print("feature_train shape: row %d col %d" % (np.shape(feature_train)[0], np.shape(feature_train)[1])) 
        print("feature_test shape: row:%d col:%d" % (np.shape(feature_test)[0], np.shape(feature_test)[1]))
        print("feature_train shape: row %d" % (np.shape(label_train)[0]))
        print("feature_train shape: row %d" % (np.shape(label_test)[0]))
        for i in range(2, 10):
            subtrains = feature_train[:, 0:i]
            subtests = feature_test[:, 0:i]
            (scores, tt, tf, ff, ft) = RF(subtrains, label_train,  subtests, label_test)
            fout.writelines(str(j) + " " + str(i) + " " + str(scores) + " " + str(tt) + " " + str(tf) + " " + str(ff) + " " + str(ft) + '\n')
    fout.close()
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
    # false example predicted as false
if __name__ == "__main__":
    fout = open("precision.txt", 'w')
    dataset = DataSetInit()
    id_clust_info = LoadPopulationDir()
    LoadData(dataset, id_clust_info)
    features = Features(dataset)
    labels = Labels(dataset)
    print ("feature row %d col %d" % np.shape(features))
    print ("label row %d " %  np.shape(labels))
    # for cross validation
    for j in range(10):
        feature_train, feature_test, label_train, label_test = train_test_split(features, labels, test_size = 0.3, random_state = 42)
        print("feature_train shape: row %d col %d" % (np.shape(feature_train)[0], np.shape(feature_train)[1])) 
        print("feature_test shape: row:%d col:%d" % (np.shape(feature_test)[0], np.shape(feature_test)[1]))
        print("feature_train shape: row %d" % (np.shape(label_train)[0]))
        print("feature_train shape: row %d" % (np.shape(label_test)[0]))
        for i in range(2, 10):
            subtrains = feature_train[:, 0:i]
            subtests = feature_test[:, 0:i]
            (scores, tt, tf, ff, ft) = RF(subtrains, label_train,  subtests, label_test)
            fout.writelines(str(j) + " " + str(i) + " " + str(scores) + " " + str(tt) + " " + str(tf) + " " + str(ff) + " " + str(ft) + '\n')
    fout.close()
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
    # false example predicted as false
if __name__ == "__main__":
    fout = open("precision.txt", 'w')
    dataset = DataSetInit()
    id_clust_info = LoadPopulationDir()
    LoadData(dataset, id_clust_info)
    features = Features(dataset)
    labels = Labels(dataset)
    print ("feature row %d col %d" % np.shape(features))
    print ("label row %d " %  np.shape(labels))
    # for cross validation
    for j in range(10):
        feature_train, feature_test, label_train, label_test = train_test_split(features, labels, test_size = 0.3, random_state = 42)
        print("feature_train shape: row %d col %d" % (np.shape(feature_train)[0], np.shape(feature_train)[1])) 
        print("feature_test shape: row:%d col:%d" % (np.shape(feature_test)[0], np.shape(feature_test)[1]))
        print("feature_train shape: row %d" % (np.shape(label_train)[0]))
        print("feature_train shape: row %d" % (np.shape(label_test)[0]))
        for i in range(2, 10):
            subtrains = feature_train[:, 0:i]
            subtests = feature_test[:, 0:i]
            (scores, tt, tf, ff, ft) = RF(subtrains, label_train,  subtests, label_test)
            fout.writelines(str(j) + " " + str(i) + " " + str(scores) + " " + str(tt) + " " + str(tf) + " " + str(ff) + " " + str(ft) + '\n')
    fout.close()
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
    # false example predicted as false
if __name__ == "__main__":
    fout = open("precision.txt", 'w')
    dataset = DataSetInit()
    id_clust_info = LoadPopulationDir()
    LoadData(dataset, id_clust_info)
    features = Features(dataset)
    labels = Labels(dataset)
    print ("feature row %d col %d" % np.shape(features))
    print ("label row %d " %  np.shape(labels))
    # for cross validation
    for j in range(10):
        feature_train, feature_test, label_train, label_test = train_test_split(features, labels, test_size = 0.3, random_state = 42)
        print("feature_train shape: row %d col %d" % (np.shape(feature_train)[0], np.shape(feature_train)[1])) 
        print("feature_test shape: row:%d col:%d" % (np.shape(feature_test)[0], np.shape(feature_test)[1]))
        print("feature_train shape: row %d" % (np.shape(label_train)[0]))
        print("feature_train shape: row %d" % (np.shape(label_test)[0]))
        for i in range(2, 10):
            subtrains = feature_train[:, 0:i]
            subtests = feature_test[:, 0:i]
            (scores, tt, tf, ff, ft) = RF(subtrains, label_train,  subtests, label_test)
            fout.writelines(str(j) + " " + str(i) + " " + str(scores) + " " + str(tt) + " " + str(tf) + " " + str(ff) + " " + str(ft) + '\n')
    fout.close()
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
    # false example predicted as false
if __name__ == "__main__":
    fout = open("precision.txt", 'w')
    dataset = DataSetInit()
    id_clust_info = LoadPopulationDir()
    LoadData(dataset, id_clust_info)
    features = Features(dataset)
    labels = Labels(dataset)
    print ("feature row %d col %d" % np.shape(features))
    print ("label row %d " %  np.shape(labels))
    # for cross validation
    for j in range(10):
        feature_train, feature_test, label_train, label_test = train_test_split(features, labels, test_size = 0.3, random_state = 42)
        print("feature_train shape: row %d col %d" % (np.shape(feature_train)[0], np.shape(feature_train)[1])) 
        print("feature_test shape: row:%d col:%d" % (np.shape(feature_test)[0], np.shape(feature_test)[1]))
        print("feature_train shape: row %d" % (np.shape(label_train)[0]))
        print("feature_train shape: row %d" % (np.shape(label_test)[0]))
        for i in range(2, 10):
            subtrains = feature_train[:, 0:i]
            subtests = feature_test[:, 0:i]
            (scores, tt, tf, ff, ft) = RF(subtrains, label_train,  subtests, label_test)
            fout.writelines(str(j) + " " + str(i) + " " + str(scores) + " " + str(tt) + " " + str(tf) + " " + str(ff) + " " + str(ft) + '\n')
    fout.close()
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
    # false example predicted as false
if __name__ == "__main__":
    fout = open("precision.txt", 'w')
    dataset = DataSetInit()
    id_clust_info = LoadPopulationDir()
    LoadData(dataset, id_clust_info)
    features = Features(dataset)
    labels = Labels(dataset)
    print ("feature row %d col %d" % np.shape(features))
    print ("label row %d " %  np.shape(labels))
    # for cross validation
    for j in range(10):
        feature_train, feature_test, label_train, label_test = train_test_split(features, labels, test_size = 0.3, random_state = 42)
        print("feature_train shape: row %d col %d" % (np.shape(feature_train)[0], np.shape(feature_train)[1])) 
        print("feature_test shape: row:%d col:%d" % (np.shape(feature_test)[0], np.shape(feature_test)[1]))
        print("feature_train shape: row %d" % (np.shape(label_train)[0]))
        print("feature_train shape: row %d" % (np.shape(label_test)[0]))
        for i in range(2, 10):
            subtrains = feature_train[:, 0:i]
            subtests = feature_test[:, 0:i]
            (scores, tt, tf, ff, ft) = RF(subtrains, label_train,  subtests, label_test)
            fout.writelines(str(j) + " " + str(i) + " " + str(scores) + " " + str(tt) + " " + str(tf) + " " + str(ff) + " " + str(ft) + '\n')
    fout.close()
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
    # false example predicted as false
if __name__ == "__main__":
    fout = open("precision.txt", 'w')
    dataset = DataSetInit()
    id_clust_info = LoadPopulationDir()
    LoadData(dataset, id_clust_info)
    features = Features(dataset)
    labels = Labels(dataset)
    print ("feature row %d col %d" % np.shape(features))
    print ("label row %d " %  np.shape(labels))
    # for cross validation
    for j in range(10):
        feature_train, feature_test, label_train, label_test = train_test_split(features, labels, test_size = 0.3, random_state = 42)
        print("feature_train shape: row %d col %d" % (np.shape(feature_train)[0], np.shape(feature_train)[1])) 
        print("feature_test shape: row:%d col:%d" % (np.shape(feature_test)[0], np.shape(feature_test)[1]))
        print("feature_train shape: row %d" % (np.shape(label_train)[0]))
        print("feature_train shape: row %d" % (np.shape(label_test)[0]))
        for i in range(2, 10):
            subtrains = feature_train[:, 0:i]
            subtests = feature_test[:, 0:i]
            (scores, tt, tf, ff, ft) = RF(subtrains, label_train,  subtests, label_test)
            fout.writelines(str(j) + " " + str(i) + " " + str(scores) + " " + str(tt) + " " + str(tf) + " " + str(ff) + " " + str(ft) + '\n')
    fout.close()
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
def DataSetInit():
