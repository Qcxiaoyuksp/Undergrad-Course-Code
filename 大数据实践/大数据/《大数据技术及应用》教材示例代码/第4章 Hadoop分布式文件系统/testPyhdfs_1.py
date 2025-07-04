import pyhdfs
client= pyhdfs.HdfsClient(hosts="localhost:9870",user_name="hadoop")
#client.mkdirs("/data")
for file in client.listdir("/"):
    print(file)