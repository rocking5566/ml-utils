import keras
from sklearn.metrics import roc_auc_score
import sys
import matplotlib.pyplot as plt
from keras.models import Model
import numpy as np


class Histories(keras.callbacks.Callback):
	def __init__(self):
		return

	def on_train_begin(self, logs={}):
		return

	def on_train_end(self, logs={}):
		return

	def on_epoch_begin(self, epoch, logs={}):
		return

	def on_epoch_end(self, epoch, logs={}):
		input = self.model.input #this can be a list or a matrix.
		labels = np.argmax(self.validation_data[1],axis=1) #make one-hot vector to index for visualization
		
		visualizer = Model(inputs=input, outputs=self.model.get_layer('visualize_layer').output)
		distribute_2d = visualizer.predict(self.validation_data[0])
		
		visualize(distribute_2d, labels,epoch)
		
		return

	def on_batch_begin(self, batch, logs={}):
		return

	def on_batch_end(self, batch, logs={}):
		return


def visualize(feat, labels, epoch):

    plt.ion()
    c = ['#ff0000', '#ffff00', '#00ff00', '#00ffff', '#0000ff',
         '#ff00ff', '#990000', '#999900', '#009900', '#009999']
    plt.clf()
    for i in range(10):
        plt.plot(feat[labels == i, 0], feat[labels == i, 1], '.', c=c[i])
    plt.legend(['0', '1', '2', '3', '4', '5', '6', '7', '8', '9'], loc = 'upper right')
    XMax = np.max(feat[:,0]) 
    XMin = np.min(feat[:,1])
    YMax = np.max(feat[:,0])
    YMin = np.min(feat[:,1])

    plt.xlim(xmin=XMin,xmax=XMax)
    plt.ylim(ymin=YMin,ymax=YMax)
    plt.text(XMin,YMax,"epoch=%d" % epoch)
    #plt.savefig('./images/epoch=%d.jpg' % epoch)
    plt.draw()
    plt.pause(0.001)