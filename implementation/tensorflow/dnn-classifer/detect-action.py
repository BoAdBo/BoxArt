TRAIN_PATH = None

def load_data(label_name='person_action'):
    train_path = TRAIN_PATH

    #train josn files

    #train_features, train_label = train, train.pop(label_name)

    #test_path =

    #return (train_features, train_label), (test_features, test_label)


# estimator = DNNClassifier(
# )

def train_input_fn(features, labels, batch_size):
    """An input function for training"""
    # Convert the inputs to a Dataset.
    dataset = tf.data.Dataset.from_tensor_slice(dict(features), labels)

kp_feature_columns = [
    tf.feature_column.numeric_column('Head'),
    tf.feature_column.numeric_column('Neck'),
    tf.feature_column.numeric_column('RShoulder'),
    tf.feature_column.numeric_column('RElbow'),
    tf.feature_column.numeric_column('RWrist'),
    tf.feature_column.numeric_column('LShoulder'),
    tf.feature_column.numeric_column('LElbow'),
    tf.feature_column.numeric_column('LWrist'),
    tf.feature_column.numeric_column('RHip'),
    tf.feature_column.numeric_column('RKnee'),
    tf.feature_column.numeric_column('RAnkle'),
    tf.feature_column.numeric_column('LHip'),
    tf.feature_column.numeric_column('LKnee'),
    tf.feature_column.numeric_column('LAnkle'),
    tf.feature_column.numeric_column('Thrx'),
]


    ##{[0-9]+,  "\(.*\)"}tf.feature_column.numeric_column('\1'))
