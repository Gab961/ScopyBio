**********************************************************************************************
*                                   ScopyBio                                                 *
**********************************************************************************************
For build this project we need some tools 

	* cmake (https://cmake.org/)
	* compilater for your operating system (g++,minGW,clang ...)
	* conan (package manager)(https://conan.io/)

after you are succefuly install all previous tools, you need to execute some command for build projects 

	* $ conan remote add arsen-deps https://api.bintray.com/conan/arsen-studio/arsen-deps
	* $ conan remote add bincrafters https://api.bintray.com/conan/bincrafters/public-conan
	* go on build repesitory in /ScopyBio
	* execute conan
		-Linux : $ conan install .. -s build_type=Release --build=missing
		-Windows : $ conan install .. -s build_type=Release -s compiler='VisualStudio" -s compiler.runtime=MDd --build=missing
Forcing compilation with gcc = 9.2 :
	* $ conan install .. -s compiler.version=9.2 --build gtest --build jsoncpp --build libjpeg --build libwebp --build protobuf --build zlib --build OpenSSL --build jasper --build libpng --build libtiff --build openexr --build libcurl --build libssh2 --build opencv --build libgit2

	* $ cmake ..
	* $ cmake --build .


Now you have a ScopyBio.exe in Build/bin/ 
