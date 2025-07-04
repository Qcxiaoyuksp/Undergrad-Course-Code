from pyhdfs import HdfsClient

def create_directory(hdfs_path):
    client = HdfsClient(hosts="localhost:9870", user_name="hadoop")
    try:
        client.mkdirs(hdfs_path)
        print(f"Directory '{hdfs_path}' created successfully.")
    except Exception as e:
        print(f"Failed to create directory '{hdfs_path}': {e}")

# 创建一个名为 'test1' 的目录
create_directory("/test1")