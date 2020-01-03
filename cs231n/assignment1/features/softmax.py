from builtins import range
import numpy as np
from random import shuffle
from past.builtins import xrange

def softmax_loss_naive(W, X, y, reg):
    """
    Softmax loss function, naive implementation (with loops)

    Inputs have dimension D, there are C classes, and we operate on minibatches
    of N examples.

    Inputs:
    - W: A numpy array of shape (D, C) containing weights.
    - X: A numpy array of shape (N, D) containing a minibatch of data.
    - y: A numpy array of shape (N,) containing training labels; y[i] = c means
      that X[i] has label c, where 0 <= c < C.
    - reg: (float) regularization strength

    Returns a tuple of:
    - loss as single float
    - gradient with respect to weights W; an array of same shape as W
    """
    # Initialize the loss and gradient to zero.
    num_train = X.shape[0]
    num_classes = W.shape[1]
    num_dim = X.shape[1]

    loss = 0.0
    dW = np.zeros_like(W)

    #############################################################################
    # TODO: Compute the softmax loss and its gradient using explicit loops.     #
    # Store the loss in loss and the gradient in dW. If you are not careful     #
    # here, it is easy to run into numeric instability. Don't forget the        #
    # regularization!                                                           #
    #############################################################################
    # *****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    # Compute loss
    raw_prob = X.dot(W)
    exp_prob = np.exp(raw_prob)

    exp_sum = np.sum(exp_prob, axis=1)
    exp_true = exp_prob[range(num_train), y]
    exp_quot = exp_true/exp_sum

    per_element_loss = -np.log(exp_quot)

    loss = np.sum(per_element_loss)/num_train + reg * np.sum(W*W)

    # Compute gradient

    def calculate_back_for_class(train, im_class):
        e_power_factor = np.exp(raw_prob[i, im_class])

        dW = np.zeros_like(W)
        dW[:,im_class] = X[i] * e_power_factor

        return dW


    for i in range(num_train):
        true_label = y[i]

        forw_dividend = exp_true[i]
        forw_divider = exp_sum[i]
        forw_quotient = -1/exp_quot[i]

        back_dividend = calculate_back_for_class(i, true_label)
        back_divider = sum(calculate_back_for_class(i, j) for j in range(num_classes))

        main_term = forw_quotient * (((back_dividend * forw_divider) -
            (back_divider * forw_dividend)) / (forw_divider ** 2))

        dW += main_term

    dW /= num_train
    dW += reg * 2 * W
    # *****END OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    return loss, dW


def softmax_loss_vectorized(W, X, y, reg):
    """
    Softmax loss function, vectorized version.

    Inputs and outputs are the same as softmax_loss_naive.
    """
    # Initialize the loss and gradient to zero.
    loss = 0.0
    dW = np.zeros_like(W)

    num_train = X.shape[0]
    num_classes = W.shape[1]
    num_dim = X.shape[1]

    loss = 0.0
    dW = np.zeros_like(W)


    #############################################################################
    # TODO: Compute the softmax loss and its gradient using no explicit loops.  #
    # Store the loss in loss and the gradient in dW. If you are not careful     #
    # here, it is easy to run into numeric instability. Don't forget the        #
    # regularization!                                                           #
    #############################################################################
    # *****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    # Compute loss
    raw_prob = X.dot(W)
    exp_prob = np.exp(raw_prob)

    exp_sum = np.sum(exp_prob, axis=1)
    exp_true = exp_prob[range(num_train), y]
    exp_quot = exp_true/exp_sum

    per_element_loss = -np.log(exp_quot)

    loss = np.sum(per_element_loss)/num_train + reg * np.sum(W*W)

    #Compute weights

    # Train to labels
    TtL = np.zeros((num_train, num_classes))
    TtL[range(num_train), y] = 1

    # First term of divide derivative
    forw_quotient = -1/exp_quot
    forw_divider = exp_sum

    e_power_true_factor = np.exp(raw_prob[range(num_train), y])
    factor = forw_quotient / forw_divider * e_power_true_factor

    dW = (X * np.expand_dims(factor, axis=1)).T.dot(TtL)

    # Second term of divide derivation
    forw_quotient = -1/exp_quot

    forw_dividend = exp_true
    forw_divider = exp_sum

    e_power_factor = np.exp(raw_prob)

    dW -= (X * np.expand_dims(forw_quotient * forw_dividend / (forw_divider ** 2), 1)).T.dot(e_power_factor)

    dW /= num_train
    dW += reg * 2 * W

    # *****END OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    return loss, dW
