## Units

units of position, speed, time and acceleration are designed to be as low-level as possible.

**position**: centipixels (cpx) 10 cpx = 1px on screen.
**velocity**: centipixels per frame (cpx/fm). To avoid bodies passing through each other without colliding, this has a natural limit of `v = 10` (or one pixel per frame). This isn't as limiting as it seems, as the frame rate of the arduboy loops may be set so that v = 1 appears to be arbitrarily fast. To achieve the effect of v appearing to be some speed, v' where v' has units `px/s`:

>v' = (fps/10) * v

**acceleration**: centipixels per frame per frame (cpx/fm^2)

>a' = (fps^2/10) * a

**time**: "time" is measured by frames. game time and human time are mapped by the fps of the arduino game.

## Collision Resolution
collision resolution is based on two bodies existing in the same space, or touching, on a single frame. Since it isn't based on projecting movement vectors, it means that a limiting factor is that no one body be able to move faster than 10cpx/fm. Manipulating the fps is how you would achieve "faster" and "slower" real time play.


TO DO:
1 - Implement sprite printer using sprite manager and printer.
2 - create entity factory method/builder. entity is the only way to insert into force field. (could hide force field with facade pattern, e.g. Game.addEntity(Entity)). entity would be stripped into forceBody etc.
