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

	* $ cmake ..
	* $ cmake --build .


Now you have a ScopyBio.exe in Build/bin/ 
