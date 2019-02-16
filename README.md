For cpp and boost learn

If can't find any lib, please use "export LD_LIBRARY_PATH=/usr/local/lib" commands.

use glog


ubuntu install(recommand):

sudo apt-get install libgoogle-glog-dev

uninstall:

sudo apt-get uninstall libgoogle-glog-dev


source install: 

git clone https://github.com/google/glog.git

cd glog 
 
 
./configure

sudo apt-get install automake 

sudo autoreconf -ivf
 
mkdir build && cd build

export CXXFLAGS="-fPIC" && cmake .. && make VERBOSE=1

./configure && make && sudo make install

https://blog.csdn.net/jcjc918/article/details/51682853
https://github.com/google/glog

http://senlinzhan.github.io/2017/10/07/glog/
https://blog.csdn.net/u012348774/article/details/80620685