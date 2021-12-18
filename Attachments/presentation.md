# Pre Notes

[THE FIRST PAGE]

Good afternoon everyone.

My name is Yiming and now I'm gonna do a presentation about my computer graphics project. I will first show my demo to you, then describe how I've done them. Finally, conclusions will be made. Now let's begin!

[CLICK, NOW PAGE 1]

This is my project scene, As the Wind. With the breeze blows and the grass shakes, I want to describe a quiet and peaceful space for you to dream and relax. You can see that the clouds and the moon is moving slightly, and these trees are also shaking.

I hope you enjoy this scene. The idea of creating such a scene comes from a game, Harry Potter: Magic Awakened, and I may show you a video of this. I want you to notice that how this game builds the trees. It's a twenty-second video.

[CLICK, NOW PAGE 2]

Now let’s go to the second part. I think you may be curious how to build a tree like this, so in this part, I would discuss how to build such a tree.

I would like to replay this video again. We focus on this tree. Note that it seems that it looks the same at every angle. We also can find that there are six 'leaves' -- we call these things 'leaves' now for convenience -- in this tree.

Okay, so I've extracted the tree as an asset from the screenshot of this game.

[CLICK, NOW PAGE 3]

One thing to clarify, is that this is still a rectangle image, which means that every pixel now, of pure white colour, is transparent, or we can say that they are of 0 alpha value. If you copy this image to any other background image using most of the softwares, like Photoshop, then these areas should be disappeared. We will talk about this more later.

You may have got an impression on this. Let me explain how to make this picture 3D:

[CLICK, NOW PAGE 4]

So suppose this blue rectangle is the tree image. 

[CLICK, NOW PAGE 4]

We copy this 2 times, so we can get 3 tree images. we ROTATE them each 60 degrees by their midlines, and put them together with their midlines aligned, we can get such a shape. It looks like stacked snowflakes. This is what we want to do. We put the 'leaves' together to build a tree.

[CLICK, NOW PAGE 5]

Back to the tree image, we will perform the same thing. You see that if two more 'leaves' are added, THEORETICALLY it looks more three-dimensional.

[CLICK, NOW PAGE 6]

Talk is less, show me the code. In the class of Tree, I draw it like this. You may take a look at this line of code, glColor3f(), which will also be discussed later.

Now it's the time to run the code!

[CLICK, NOW PAGE 7]

... But it seems not correct. As you can see on the right hand side, at the top is what we want, in the middle is the line of code, glColor3f(), and at the bottom is the texture picture that we use. You see it's very strange: It is neither the correct background colour, nor the correct tree colour.

Well, we have to find more about OpenGL's secret. After more experiments, THIS

[CLICK, NOW PAGE 8]

shows a better result. We changed the texture image’s background colour from white to green. Now the background colour has been removed, although the colour is strange.

[CLICK, NOW PAGE 9]

After more experiments, I have changed the glColor3f function from white to green, and the colour is somehow good: even though our image is a white tree. It is transparent somehow, but if we 'plant' more trees, it looks like this.

[CLICK, NOW PAGE 10]

It is of good visualisation. I think, the way I build these models is the most creative thing in this project. I am satisfied that I successfully implemented this idea!

[CLICK, NOW PAGE 11]

As for the shaking grasses, they are built by the same process with trees. You may check this video for more details. 

[CLICK, NOW PAGE 11]

For their movement, all I had done is to apply 2 sin function in both x axis and z axis. You may check the code for more details.

[CLICK, NOW PAGE 12]

Note the 2 sin functions. I changed the parameters again and again to make the movement more realistic.

[CLICK, NOW PAGE 13]

As for the moon and the clouds, the moon is created by gluSolidSphere, and the clouds are simple textured planes that is rotating around y axis. So again this is the result.



Well, let's make a conclusion here. I think the most interesting thing is that I realised that OpenGL is the most basic ones, with no help from game engines or 3D softwares. By doing this project I took experiments on OpenGL and C++, getting deeper understanding about them; it's really a hard time to make a project, thanks to the guys who helped and encouraged me. Finally, many thanks to all of you listening to such a long presentation. 

That's all. Thanks for your listening and have a good day!