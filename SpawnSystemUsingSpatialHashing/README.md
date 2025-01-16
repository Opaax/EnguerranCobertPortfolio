Dynamic Spawn System Based on Player Position

I was initially searching for a grid hash system when I stumbled upon the TPointHashGrid3d class within the Spatial namespace of GeometryCore. You can find more details about it here: TPointHashGrid3d Documentation.

To simplify usage and extend its functionality, I created a custom plugin that wraps around TPointHashGrid3d, providing additional custom handling and features.

Currently, my spawn system is relatively simple:
- Using predefined spawn data, I specify a minimum spawn range and a maximum spawn range from the player.
- The system calculates all possible spawn locations within that range.
- A random location is selected from the valid options, and voilà—the spawn occurs!

For future improvements, I may need to create a fully custom system that allows the creation of cells with customizable sizes for each component. This would provide greater flexibility, enabling me to:
- Define cell dimensions dynamically based on the specific needs of individual components.
- Optimize performance by tailoring cell sizes to balance precision and efficiency.
- Expand the system to support more complex spawn rules and interactions between cells.

![image](https://github.com/user-attachments/assets/f8a02a65-9bb8-4640-bac1-c0731c5c95c9)
![image](https://github.com/user-attachments/assets/347212e3-93eb-4894-8c3b-91ef1ba886e4)
