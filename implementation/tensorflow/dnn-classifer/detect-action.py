
###############################
### configuration variables ###
###############################

""" training_path, test_path, and evaluation_path by default only parse json file"""
DEFAULT = {'batch_size': 100 ,
           'train_steps': 1000 ,
           'training_path': '',
           'test_path': '',
           'evaluation_path': ''}

x_offset, y_offset = 0, 1
i_offset = 3

KEYPOINT_COLUMNS = [
        'HEAD',
        'Neck',
        'RShoulder',
        'RElbow',
        'RWrist',
        'LShoulder',
        'LElbow',
        'LWrist',
        'RHip',
        'RKnee',
        'RAnkle',
        'LHip',
        'LKnee',
        'LAnkle',
        'Thrx',
]

# lambda x: KEYPOINT_COLUMNS[x/i_offset] + \
#     ('_x' if (x % i_offset == x_offset)
#      else '_y' if (x % i_offset == y_offset)
#      else '_confidence')

# lambda x: KEYPOINT_COLUMNS[x/i_offset] + \
#     ('_x' if (x % i_offset == x_offset) else '_y')

# joints.ix[:, joints.columns % 3 != 2]

#######################
### tensorflow code ###
#######################

import argparse
import tensorflow as tf
import pandas as pd

parser = argparse.ArgumentParser()
parser.add_argument('--batch_size', default=DEFAULT['batch_size'], type=int, help='batch size')
parser.add_argument('--train_steps', default=DEFAULT['train_steps'], type=int,
                    help='number of training steps')
parser.add_argument()

def load_data(y_name='label'):
    train = pd.read_json(DEFAULT['training_path'])
    test = pd.read_json(DEFAULT['test_path'])

    train.pop('image_name')
    test.pop('image_name')

    train_x, train_y = train, train.pop(y_name)
    test_x, test_y = test, test.pop(y_name)

    # expand list to columns
    train_kp = train_x['joints'].apply(pd.Series)
    test_kp = test_x['joints'].apply(pd.Series)

    # trim off confidence
    train_kp = train_kp.ix[:, joints.columns % 3 != 2]
    test_kp = test_kp.ix[:, joints.columns % 3 != 2]

    rename_function = lambda x: KEYPOINT_COLUMNS[x / i_offset] + \
        ('_x' if (x % i_offset == x_offset) else '_y')

    # rename tags
    train_kp = train_kp.rename(columns=rename_function)
    test_kp = test_kp.rename(columns=rename_function)

    # assign back
    train_x = train_kp
    test_x = test_kp

    return (train_x, train_y), (test_x, test_y)

def train_input_fn(features, labels, batch_size):
    """An input function for training"""
    # Convert the inputs to a Dataset.
    dataset = tf.data.Dataset.from_tensor_slice(dict(features), labels)

    dataset = dataset.shuffle(1000),repeat().batch(batch_size)

    return dataset

    ##{[0-9]+,  "\(.*\)"}tf.feature_column.numeric_column('\1'))

def main(argv):

    (train_x, train_y), (test_x, test_y) = load_data()

    kp_feature_columns = []
    for key in train_x.keys():
        my_feature_columns.append(tf.feature_column.numeric_column(key=key))

    # kp_feature_columns = [
    #     tf.feature_column.numeric_column('Head'),
    #     tf.feature_column.numeric_column('Neck'),
    #     tf.feature_column.numeric_column('RShoulder'),
    #     tf.feature_column.numeric_column('RElbow'),
    #     tf.feature_column.numeric_column('RWrist'),
    #     tf.feature_column.numeric_column('LShoulder'),
    #     tf.feature_column.numeric_column('LElbow'),
    #     tf.feature_column.numeric_column('LWrist'),
    #     tf.feature_column.numeric_column('RHip'),
    #     tf.feature_column.numeric_column('RKnee'),
    #     tf.feature_column.numeric_column('RAnkle'),
    #     tf.feature_column.numeric_column('LHip'),
    #     tf.feature_column.numeric_column('LKnee'),
    #     tf.feature_column.numeric_column('LAnkle'),
    #     tf.feature_column.numeric_column('Thrx'),
    # ]

    args = parser.parse_args(argv[1:])
    classifiter = tf.estimator.DNNClassifier(
        feature_columns=kp_feature_columns,
        hidden_units=[30, 30],
        n_classes=10)

    classifier.train(
        input_fn=lambda:train_input_fn(train_x, train_y,
                                       args.batch_size),
        steps=args.train_steps)

    eval_result = classifier.evaluate(
        input_fn=lambda:eval_input_fn(test_x, test_y,
                                      args.batch_size))
    print()
