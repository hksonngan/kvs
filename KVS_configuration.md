# Configuration #
It is necessary to set an environment variable 'KVS\_DIR' before compiling KVS. The compiled libraries and header files are installed into the directory specified by it. And some KVS command line applications are installed into 'KVS\_DIR/bin'. Therefore, the user have to add its directory to environment variable 'PATH'. Some examples of the configurations are shown here.

## Windows ##
For Windows,  the environment variables can be set by using the System Properties dialog. Open 'Control Panel' -> 'Performance and Maintenance' -> 'System', or right-click on My Computer and choose the 'Properties'. And then, click the 'Advanced' tab in the dialog and the following variables can be set by clicking the 'Environment Variables' button.

| **Variable** | **Value** |
|:-------------|:----------|
| KVS\_DIR     | C:\Program Files\kvs |
| PATH         | %PATH%;%KVS\_DIR%\bin |

## Linux and Mac OS X ##
For Linux and Mac OS X,  the environment variables can be set as follows. For bash, the following descriptions should be added to .bashrc.

```
export KVS_DIR=/usr/local/kvs
export PATH=$KVS_DIR/bin:$PATH
```