import keras
from keras import backend as K


class DecayLearningRate(keras.callbacks.Callback):
    def __init__(self, decay_epochs, decay_rates):
        assert(len(decay_epochs) == len(decay_rates))
        self.decay_epochs = decay_epochs
        self.decay_rates = decay_rates

    def on_train_begin(self, logs={}):
        return

    def on_train_end(self, logs={}):
        return

    def on_epoch_begin(self, epoch, logs={}):

        for idx, decay_epoch in enumerate(self.decay_epochs):
            if epoch == decay_epoch:
                lr = K.get_value(self.model.optimizer.lr)
                K.set_value(self.model.optimizer.lr, lr * self.decay_rates[idx])
                break

        return
