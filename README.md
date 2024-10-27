For my final project in CS 330, I chose to create a 3D scene that represents an almost finished game of pool. This scene captures the moment when the majority of the balls have been potted, leaving only a few remaining, with the pool cue and triangle placed prominently on the table. The goal of the scene was to use various basic and complex shapes to accurately depict the objects typically found in a pool game setup, while ensuring that the representation aligned with the client’s needs.

The project involves several 3D objects, each chosen and designed to clearly represent a pool game. The complex objects in the scene include the pool cue and the triangle rack. The pool cue was modeled using multiple primitive shapes—a cylinder for the main body, a slightly tapered cylinder for the ferrule, and a smaller cylinder for the tip. These shapes were combined and scaled accordingly to create a realistic appearance. For the texture, I applied polished wood for the main body, black wood for the ferrule, and blue chalk for the tip, aligning with a real-life pool cue. 

The triangle rack is another complex object in the scene. To replicate the real-life triangular shape that holds the balls at the start of a game, I utilized 3 box meshs to outline the triangular form with a hole in the center, making it suitable for a pool setup. The goal was to create an object that had the correct shape and maintained a consistent visual style with the rest of the table.

The remaining objects are simpler in nature, mainly consisting of spheres that represent the pool balls. These were designed using a basic sphere mesh and are positioned on the table to mimic the scattered layout of a game in progress. Each sphere was textured with distinct color patterns to differentiate between the solids and stripes, consistent with real pool balls. Additionally, I included a small cube as the chalk, another simple object placed on the side of the table. The chalk’s texture reflects its slightly rough and worn appearance, adding to the realism of the scene.

Lighting and Camera
For lighting, I incorporated two light sources to create a polished visualization of the 3D models. One is a white directional light to provide even coverage across the scene, ensuring that the objects remain visible from all camera angles. The second is a point light positioned above the table to simulate an overhead fixture, with a warm tint to emulate the ambient lighting commonly found in pool halls. The Phong shading model is applied, utilizing ambient, diffuse, and specular components to give the objects a realistic and polished look.

The camera setup allows for both horizontal, vertical, and depth navigation around the 3D scene. The user can move through the scene using WASD for directional movement, QE for vertical control, and the mouse cursor to change the camera's orientation. The mouse scroll further controls the speed of camera movement, providing users with precise control. 


Now here are some answers for the class:

How do I approach designing software?
I start by thinking about what the software needs to do, breaking down the main goals into smaller tasks, then planning how the code and visuals will come together to meet those goals.

What new design skills has your work on the project helped you to craft?
I learned to focus on balancing visual details with performance, like optimizing textures and lighting for a smoother 3D experience without overloading the system.

What design process did you follow for your project work?
I followed a simple plan: sketching ideas, defining the main elements, then building each piece step-by-step and testing as I went.

How could tactics from your design approach be applied in future work?
Planning out visuals and breaking down tasks can help keep future projects organized, making it easier to adjust details as needed.

How do I approach developing programs?
I start by planning the basic structure, writing small parts, testing often, and fixing any issues before moving on.

What new development strategies did you use while working on your 3D scene?
I learned to use modular coding—creating separate pieces of code for different objects—making it easier to work on each one individually.

How did iteration factor into your development?
I kept making small changes, testing them, and improving based on what I saw, which helped me refine the scene step-by-step.

How has your approach to developing code evolved throughout the milestones, which led you to the project’s completion?
I got better at organizing my code and planning ahead, so I made fewer mistakes and could improve my scene more efficiently.

How can computer science help me in reaching my goals?
Computer science gives me skills in problem-solving and creating digital tools, which will be useful in any tech-related job I pursue.

How do computational graphics and visualizations give you new knowledge and skills that can be applied in your future educational pathway?
They teach me how to create and work with visuals in code, which will be helpful in any project that involves user interfaces or visual data.

How do computational graphics and visualizations give you new knowledge and skills that can be applied in your future professional pathway?
They help me understand how to make visuals interactive and realistic, which is useful in fields like game design, web development, or any work that involves visual storytelling.

Development Choices 
My development choices were focused on simplicity while ensuring an accurate and recognizable representation of a pool game. Using basic shapes for objects like the spheres and chalk made the modeling process efficient, while applying transformations and combining shapes for the pool cue and triangle allowed for more complexity without exceeding the triangle count limit. 

