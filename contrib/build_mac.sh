cd ..
CXXFLAGS="-I/usr/include -I/usr/local/include -stdlib=libc++" LDFLAGS="-L/usr/lib -L/usr/local/include" qmake BOOST_LIB_SUFFIX=-mt BOOST_LIB_PATH=/usr/local/Cellar/boost/1.67.0_1/lib BOOST_INCLUDE_PATH=/usr/local/Cellar/boost/1.67.0_1/include/ BDB_INCLUDE_PATH=/usr/local/opt/berkeley-db@4/include BDB_LIB_PATH=/usr/local/opt/berkeley-db@4/lib OPENSSL_INCLUDE_PATH=/usr/local/opt/openssl/include OPENSSL_LIB_PATH=/usr/local/opt/openssl/lib USE_LEVELDB=1 MINIUPNPC_INCLUDE_PATH=/usr/local/include/ MINIUPNPC_LIB_PATH=/usr/local/lib
make