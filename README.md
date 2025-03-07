# Cub3d
**The objective of this project is to make a dynamic view inside a maze, in which you’ll have to find your way**

> [!NOTE]
> This project is inspired by the world-famous Wolfenstein 3D game, which was the first FPS ever.

# Index
* [What is Raycasting?](#raycasting)
* [How to control](#controls)
* [Bonus](#bonus)
* [Usage](#usage)
* [Final Grade](#grade)

## Raycasting
#### Given a point and a polygon, check if the point is inside or outside the polygon using the **ray-casting algorithm.**
- The function ray_intersects_segment return **true** if the horizontal ray starting from the point P intersects the side (segment), returns **false** otherwise.

_A pseudocode can be simply:_
```
 count ← 0
 foreach side in polygon:
   if ray_intersects_segment(P,side) then
     count ← count + 1
 if is_odd(count) then
   return inside
 else
   return outside
```

![5cd4613e480e4fba228a837d63ff3cd68506e1f8](https://github.com/user-attachments/assets/dc18ae73-8218-4cea-bf4f-d7a4073fe829)



## Controls
- **W:** move forward
- **S:** move backward
- **A:** strafe left
- **D:** strafe right
- **left arrow:** rotate left
- **right arrow:** rotate right

## Bonus
- Wall collisions ✔️
- A minimap systemM ✔️
- Doors which can open and close ❌
- animated sprite ❌
- Rotate the point of view with the mouse ❌

## Usage

1. Clone this repository:

```
git clone github.com/shoganaix/Cub3d

```

2. Compile and run your program:

```
make
./Cub3d maps/map1.cub (select any .cub file inside our map folder)
```

## Grade
