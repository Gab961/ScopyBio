***********************************************
*					ScopyBio				  *
***********************************************
For build this project we need some tools 

	* cmake (https://cmake.org/)
	* compilater for your operating system (g++,minGW,clang ...)
	* conan (package manager)(https://conan.io/)

after you are succefuly install all previous tools, you need to execute some command for build projects 

	* $ conan remote add arsen-deps https://api.bintray.com/conan/arsen-studio/arsen-deps
	* $ conan remote add bincrafters https://api.bintray.com/conan/bincrafters/public-conan
	* go on build repesitory in /ScopyBio
	* $ conan install .. --build gtest --build protobuf --build jasper --build openexr --build opencv --build OpenSSL --build libcurl --build libssh2 --build libgit2
	get ready for a long time of wait

you have 