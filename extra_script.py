Import("env")

# this script is necessary to avoid errors when unit testing on the teensy

def after_upload(source, target, env):
    print("Delay while uploading...")
    import time
    time.sleep(3)
    print("Done!")

env.AddPostAction("upload", after_upload)