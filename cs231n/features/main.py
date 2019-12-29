import random
import numpy as np
import matplotlib.pyplot as plt

import data_utils
import features
import linear_classifier
import neural_net


def get_CIFAR10_data(num_training=49000, num_validation=1000, num_test=1000):
    # Load the raw CIFAR-10 data
    cifar10_dir = '../../../assignment1/cs231n/datasets/cifar-10-batches-py'

    # Cleaning up variables to prevent loading data multiple times (which may cause memory issue)
    try:
       del X_train, y_train
       del X_test, y_test
       print('Clear previously loaded data.')
    except:
       pass

    X_train, y_train, X_test, y_test = data_utils.load_CIFAR10(cifar10_dir)

    # Subsample the data
    mask = list(range(num_training, num_training + num_validation))
    X_val = X_train[mask]
    y_val = y_train[mask]
    mask = list(range(num_training))
    X_train = X_train[mask]
    y_train = y_train[mask]
    mask = list(range(num_test))
    X_test = X_test[mask]
    y_test = y_test[mask]

    return X_train, y_train, X_val, y_val, X_test, y_test

X_train, y_train, X_val, y_val, X_test, y_test = get_CIFAR10_data()

# Extract Features
# For each image we will compute a Histogram of Oriented Gradients (HOG) as well as a color histogram using the hue channel in HSV color space. We form our final feature vector for each image by concatenating the HOG and color histogram feature vectors.

# Roughly speaking, HOG should capture the texture of the image while ignoring color information, and the color histogram represents the color of the input image while ignoring texture. As a result, we expect that using both together ought to work better than using either alone. Verifying this assumption would be a good thing to try for your own interest.

# The hog_feature and color_histogram_hsv functions both operate on a single image and return a feature vector for that image. The extract_features function takes a set of images and a list of feature functions and evaluates each feature function on each image, storing the results in a matrix where each column is the concatenation of all feature vectors for a single image.

num_color_bins = 10 # Number of bins in the color histogram
feature_fns = [features.hog_feature, lambda img: features.color_histogram_hsv(img, nbin=num_color_bins)]
X_train_feats = features.extract_features(X_train, feature_fns, verbose=True)
X_val_feats = features.extract_features(X_val, feature_fns)
X_test_feats = features.extract_features(X_test, feature_fns)

# Preprocessing: Subtract the mean feature
mean_feat = np.mean(X_train_feats, axis=0, keepdims=True)
X_train_feats -= mean_feat
X_val_feats -= mean_feat
X_test_feats -= mean_feat

# Preprocessing: Divide by standard deviation. This ensures that each feature
# has roughly the same scale.
std_feat = np.std(X_train_feats, axis=0, keepdims=True)
X_train_feats /= std_feat
X_val_feats /= std_feat
X_test_feats /= std_feat

# Preprocessing: Add a bias dimension
X_train_feats = np.hstack([X_train_feats, np.ones((X_train_feats.shape[0], 1))])
X_val_feats = np.hstack([X_val_feats, np.ones((X_val_feats.shape[0], 1))])
X_test_feats = np.hstack([X_test_feats, np.ones((X_test_feats.shape[0], 1))])

# Train SVM on features
# Using the multiclass SVM code developed earlier in the assignment, train SVMs on top of the features extracted above; this should achieve better results than training SVMs directly on top of raw pixels.

# Use the validation set to tune the learning rate and regularization strength

#learning_rates = [1e-8, 1e-7, 1e-6, 1e-5]
#regularization_strengths = [8e4, 9e4, 10e4, 11e4]
#num_iters = [2500]

#results = {}
#best_val = -1
#best_svm = None

#################################################################################
## TODO:                                                                        #
## Use the validation set to set the learning rate and regularization strength. #
## This should be identical to the validation that you did for the SVM; save    #
## the best trained classifer in best_svm. You might also want to play          #
## with different numbers of bins in the color histogram. If you are careful    #
## you should be able to get accuracy of near 0.44 on the validation set.       #
#################################################################################
## *****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

#for learning_rate in learning_rates:
#    for regularization_strength in regularization_strengths:
#        for num_iter in num_iters:
#            svm = linear_classifier.LinearSVM()
#            svm.train(X_train_feats, y_train, learning_rate=learning_rate,
#                    reg=regularization_strength, num_iters=num_iter)
#            y_train_pred = svm.predict(X_train_feats)
#            y_val_pred = svm.predict(X_val_feats)

#            train_acc = np.mean(y_train == y_train_pred)
#            val_acc = np.mean(y_val == y_val_pred)

#            results[learning_rate, regularization_strength, num_iter] = train_acc, val_acc

#            if best_val < val_acc:
#                best_val = val_acc
#                best_svm = svm


## *****END OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

## Print out results.
#for lr, reg, ni in sorted(results):
#    train_accuracy, val_accuracy = results[(lr, reg, ni)]
#    print('lr %e reg %e ni %e train accuracy: %f val accuracy: %f' % (
#                lr, reg, ni, train_accuracy, val_accuracy))

#print('best validation accuracy achieved during cross-validation: %f' % best_val)

## Evaluate your trained SVM on the test set
#y_test_pred = best_svm.predict(X_test_feats)
#test_accuracy = np.mean(y_test == y_test_pred)
#print(test_accuracy)


## || lr 1.000000e-07 reg 8.000000e+04 ni 2.500000e+03 train accuracy: 0.412673 val accuracy: 0.424000
## || best validation accuracy achieved during cross-validation: 0.424000
## 0.417

## An important way to gain intuition about how an algorithm works is to
## visualize the mistakes that it makes. In this visualization, we show examples
## of images that are misclassified by our current system. The first column
## shows images that our system labeled as "plane" but whose true label is
## something other than "plane".

#examples_per_class = 8
#classes = ['plane', 'car', 'bird', 'cat', 'deer', 'dog', 'frog', 'horse', 'ship', 'truck']
#for cls, cls_name in enumerate(classes):
#    idxs = np.where((y_test != cls) & (y_test_pred == cls))[0]
#    idxs = np.random.choice(idxs, examples_per_class, replace=False)
#    for i, idx in enumerate(idxs):
#        plt.subplot(examples_per_class, len(classes), i * len(classes) + cls + 1)
#        plt.imshow(X_test[idx].astype('uint8'))
#        plt.axis('off')
#        if i == 0:
#            plt.title(cls_name)
#plt.show()

# Neural Network on image features
# Earlier in this assigment we saw that training a two-layer neural network on raw pixels achieved better classification performance than linear classifiers on raw pixels. In this notebook we have seen that linear classifiers on image features outperform linear classifiers on raw pixels.

# For completeness, we should also try training a neural network on image features. This approach should outperform all previous approaches: you should easily be able to achieve over 55% classification accuracy on the test set; our best model achieves about 60% classification accuracy.

# Preprocessing: Remove the bias dimension
# Make sure to run this cell only ONCE
print(X_train_feats.shape)
X_train_feats = X_train_feats[:, :-1]
X_val_feats = X_val_feats[:, :-1]
X_test_feats = X_test_feats[:, :-1]

print(X_train_feats.shape)

input_dim = X_train_feats.shape[1]
hidden_dim = 500
num_classes = 10


best_net = None

################################################################################
# TODO: Train a two-layer neural network on image features. You may want to    #
# cross-validate various parameters as in previous sections. Store your best   #
# model in the best_net variable.                                              #
################################################################################
# *****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

iteration_table = (2000,)
learning_rate_table = (1e-0,) #(3e-3 , 1e-4, 3e-4)
batch_size_table = (1000,)
regularization_table = (3e-4,) #(1, 0.25, 1e-1, 3e-2, 1e-2, 3e-3, 1e-3, 3e-4, 1e-4)

best_validation_performance = 0
best_train_performance = 0

for iteration in iteration_table:
    for learning_rate in learning_rate_table:
        for batch_size in batch_size_table:
            for regularization in regularization_table:
                net = neural_net.TwoLayerNet(input_dim, hidden_dim, num_classes)

                stats = net.train(X_train_feats, y_train, X_val_feats, y_val,
                num_iters=iteration, batch_size=batch_size,
                learning_rate=learning_rate,
                reg=regularization)

                train_accuracy = stats['train_acc_history'][-1]
                validation_accuracy = stats['val_acc_history'][-1]

                if validation_accuracy > best_validation_performance:
                    best_validation_performance = validation_accuracy
                    best_train_performance = train_accuracy
                    best_net = net

                print(f"Iteration: {iteration}, learning_rate: {learning_rate}, batch_size: {batch_size}, regularization: {regularization}, train: {train_accuracy}, validation_accuracy: {validation_accuracy}")

plt.subplot(2, 1, 1)
plt.plot(stats['loss_history'])
plt.title('Loss history')
plt.xlabel('Iteration')
plt.ylabel('Loss')

plt.subplot(2, 1, 2)
plt.plot(stats['train_acc_history'], label='train')
plt.plot(stats['val_acc_history'], label='val')
plt.title('Classification accuracy history')
plt.xlabel('Epoch')
plt.ylabel('Classification accuracy')
plt.legend()
plt.show()


# *****END OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

# Run your best neural net classifier on the test set. You should be able
# to get more than 55% accuracy.

test_acc = (best_net.predict(X_test_feats) == y_test).mean()
print(test_acc)

# Iteration: 2000, learning_rate: 1.0, batch_size: 1000, regularization: 0.0003, train: 0.8, validation_accuracy: 0.595
# 0.598
