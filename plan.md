* Seperate actions from visual display, necessary for animations
* make main loop which can be progressed by time, action, event
* add basic tetris functionality
* add special abilities

* Learned to use debugger
* I tried to divide task into much smaller chunks
* Experimented with incorporating features for visual debugging into every system
* ticks now progress on input, not just timer
* Max two moves without gravity applied 

score can be used to buy units and upgrades
making it into cookie clicker game

* solved blocks show +100 scores popup

* Special blocks
Cross - removes elements in cross patter giving the score
Star bomb - *
Earthquake 
Chian reaction - ignites same colour blocks
full wipe

Possible improvments:
 * Rotation should be adjusted based on rotated shape to make it look like they rotate in place

 TODO:
 * Visual effects (score pop up)

Reflection: 
    After a week worth of work of adding features onto previour version I stumbled into
    the issues I stumbled into many times, without solid foundation its only so far you
    can get.
    
    After adding just a handful of elements and improvements to the old design, I
    eventially found myself debugging thigns which broke down or did not work in a 
    way i expected them to instead of making progress.

    I decided to give a rewrite a try, in a spirit of iterative design I used pieces from
    old design which worked but took much slower approach, designing and testing one system at
    a time. This allowed me to have a very solid foundation once I got to the point where
    things started moving across the screen and user real time user input was used.

    While I did not yet got to the point with special abilities in a game I want it to be, 
    I think I am very close at getting there, where I am pretty sure I would of not had
    gotten to this point if I kept working on the old design.

    The main lesson which is not new to me, yet I often neglect it
    Rough prototyping is fine, writing untested uncommeneted code in one blob is fine for that 
    purpose.
    However, prototype should not directly morph into maintanable product, this just does
    not go well. 
    Instead, taking lessons from the prototype and research, drafting architecture of
    the product first and breking things into modules and sections. And then itterating
    on a previous protopype using the new structure and insight is much safer and more
    reliable approach delivering better results.
