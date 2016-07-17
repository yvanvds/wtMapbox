# wtMapbox
a mapbox wrapper for webtoolkit

Summary: I'm planning to write a single page application which will require good maps. Mapbox (https://www.mapbox.com) has a lot to offer, but I would like to write the server backend in c++. I've done some smaller projects with webtoolkit (https://www.webtoolkit.eu) before and think it will be a good choice for this project. But wt only has an implementation for google maps, which will not do this time. That is why i made this code.

A lot of mapbox javascript features are wrapped in c++ classes, although the library is far for complete. Still, most examples from the mapbox demo are already working without having to write any javascript code (or html and css for that matter) yourself.

I expect I will expand this library further when I have a need for it.

## Directory structure
* wtMapbox: Contains the visual studio solution
* include: The header files for the MapBox classes
* source: The cpp files for the MapBox classes
* example: A demo project with header and cpp files (this contains over 20 demo projects)
* website: the folder where the exe will be built. It also contains resources needed by the demo project.

## Building it
For a quick look, i recommend using the latest github release. For building from scratch, here's a few guidelines.

* The provided solution is created with Microsoft Visual Studio 2015 community edition.
* Webtoolkit must be downloaded and installed. (a compiled version for VS can be found here: https://github.com/kdeforche/wt/releases I used the 64bit version)
* Request a mapbox api key at https://www.mapbox.com/help/create-api-access-token/
* Copy website/wt_config.xml_orig to wt_config.xml and open this file in a text editor to add your api key
* Open the solution and open the properties. Check folder locations for debug and release. check the Additional Include Directories and Additional Library Directories.

To execute the program without VS, use the console and navigate to the website directory. Type 
    example.exe --docroot . --http-address 0.0.0.0 --http-port 8080 -c wt_config.xml
    
To view the website itself, open your browser and navigate to http://127.0.0.1:8080
