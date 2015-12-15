# Nao Face Recognition
This project consists of a little "Who Am I" demo game.  The point is to integrate use face recognition on a nao robot's cameras to be able to learn a face, put a name to that face, and then recognize that face in the future.  I also put together a neat little GUI interface for the project.  

I originally planned on incorporating the nao speech recognition API, but this additional feature has not yet been implemented.

More information on the face recognition API I used can be found [here] (https://github.com/procrob/face_recognition).  My work has been mostly structured around integrating this API to work with the nao robot's head cameras, and creating a smooth GUI interface for the API.


## Launching the Game
1. Make sure you have the correct packages installed for the NAO to work with ROS. They can be found in the tutorial [here] (http://wiki.ros.org/nao/Tutorials/Installation).

2. The package that contains the correct nodes to launch are found in nao_bringup. If you are unsure if you have the correct package installed, you can type ```roscd nao_bringup``` which should navigate you to the package, if installed properly.  If not, go through the steps of installation again. In the nao_bringup package there should be a launch file called nao.launch. This is what you will be launching when you want to use the NAO with ROS.

3. Once you are sure you have the correct package and launch file, make sure that the workspace is sourced. If you are unsure of how to go about this, the process of how to source workspaces can be found [here] (http://wiki.ros.org/ROS/Tutorials/InstallingandConfiguringROSEnvironment).

4. To launch correctly, you must know what the NAO's IP address is. To retrieve it, double tap the chest button. The NAO should say something along the lines of "Hello, my name is NAO (or whatever name he is given). My internet address is 10.0.3.16" (or whatever IP he has). 

5. Now that you have the launch file and the IP address, you can go a head and start up the nodes. To launch the file, you must type in: ```NAO_IP=10.0.3.16 roslaunch nao_bringup nao.launch```This will enable you to connect to the NAO robot.

6. To launch the 'Who Am I' demo, make sure that the workspace where the demo is located is sourced, much like you did in step 2, but with the demo package now. The demo package can be found by typing ```roscd asdinterface``` 

7. Once everything is sourced, you can launch the launch file. The launch file can be found in the asdinterface package. To launch it type: ```roslaunch asdinterface whoami.launch```. This should launch the face detection server and client, and bring up the GUI window to start the game.  After a few seconds, a window should pop up displaying the video from the nao's head camera.


## Playing the Game
1. Click the "Learn Name" button.  This should cause a little prompt in the terminal from which the launch file was launched asking for your name.  Simply type in your name and press enter to continue.  Go back to the GUI interface window for the game.  
2. Look straight into the NAO's eyes and press the "Learn Face" button.  This will enable the nao to start saving sample images of your face.  Try and move your face around slightly, iiling your head a little and making a few different faces so that the robot gets a good variety of samples.  

3. When the robot is done recoding images, the camera feed will show the last image it took of your face.  To clear away this image, simply click the "Reset Camera" button to go back to viewing the camera feed from the nao's head cameras.

4. Next, look straight into the nao's head cameras again, and click the "Who Am I?" button.  The video should draw a green box around your face with some blue text nearby labeling your face with the name you typed in earlier.  Note that this works best when you look straight at the nao robot.

5. Repeat steps 1-4 with a couple of different people.  The game should create a library of all of these people, and, while the program can only recognize one main face at a time, if you change which people look into the camera, the robot shpould be able to recognize each different face with its respective name. 

6.  If you wish to stop recognizing faces, simply click the "Reset Camera" button to return to the normal camera view.

7.  Press Shutdown to exit the game.

8.  To reset the game by removing some faces from the nao's library, see the face recognition repositiory (linked above) for proper instructions.


## Author
Victoria Albanese

## WIP
Last Updated December 15, 2015

