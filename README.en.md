# screen-recording-master

#### Description
use c/c++ achieve screen record master.base on XEngine Development for screen record software.can be record screen,record sound and package to Specify in format,and can be push desktop to stream server  
if you want to record system sound.you can download https://github.com/rdp/screen-capture-recorder-to-video-windows-free/releases and install your system

#### Software Architecture
base on xengine development.just application open source

#### compile

using x86 compile and support debug or release option

#### run

1.  download xengine module file 
2.  configure env 
3.  download this code
4.  open it to vs2019
5.  choice x86 and debug or release
6.  compile
7.  copy files in XEngine_Bin to your compile path
8.  run...

#### Instructions

1. set your desktop resolution
2. set your start pos x and y,can be set 0
3. click flush bottom and choice your sound card
4. click start
5. this software can be auto package when you stop

#### Contribution

1.  Fork the repository
2.  Create Feat_xxx branch
3.  Commit your code
4.  Create Pull Request

#### test stream media server
Push Address:rtmp://app.xyry.org/live/you code,example rtmp://app.xyry.org/live/qyt  
Pull Address:http://app.xyry.org:8088/live/you code.flv,example http://app.xyry.org:8088/live/qyt.flv

#### Description

1.  video used h264 codec.
2.  audio used aac codec
3.  default packetage as mp4 file when record complete.
4.  The SDK we provide only contains codecs and collectors
5.  this code not limit
6.  if you have a question,welcome to contact us

#### about
you can visit www.xyry.org to learn more