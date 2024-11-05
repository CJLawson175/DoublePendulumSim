<h1>Double Pendulum Simulation

<h2>Description</h2>
<b>This projects uses C Programming to simulate the motion of a double pendulum. A double pendulum is 2 rods with lengths L1 and L2 for rod1 and rod2 respectively. At the end of rod one is a mass M1 and rod 2. At the end of rod 2 there is just mass M2. The equations for motion of this system were obtained using the Euler-Lagrange equation. The units for Mass, Length and Gravity in this simulation are arbitrary. For Mass and Length the values are simply ratios M1:M2 and L1:L2. Because the Initial Conditions have a large effect on the motion of the system the Initial Conditions are also inputted by the user in radians.
</b>
<br />
 
</p>
<h2>Languages Used</h2>

- <b>C Programming</b>

<h2>Libraries Used</h2>

- <b>stdio.h</b>
- <b>stdlib.h</b>
- <b>math.h</b>
- <b>SDL2/SDL.h</b>

<h2>Compilition command for the Program</h2>
<p align="center">
<img src="https://i.imgur.com/u3CHjrA.png" height="85%" width="85%" alt="RDP event fail logs to iP Geographic information"/>

<h2>Tips:</h2>
<b>This program only simulates when initial angular velocity is 0. Inputting Initial Conditions for position such as (0.5 0.5) or (1.5 1.5) will result in no movement since it is at a point of equillibrium without a force acting upon it in the x-direction.</b>

<h2>Example 1:</h2>

- <b> M1:M2 = 1:1
- <b> L1:L2 = 1:1
- <b> Rod 1 Initial = 1*pi radians
- <b> Rod 2 Initial = 1*pi radians

<table>
<tr>
    <td><img src="https://i.imgur.com/cURaejj.png" alt="Image 1" width="600" height="350"/></td>
    <td><img src="https://i.imgur.com/BECel9P.png" alt="Image 2" width="400" height="350"/></td>
</tr>
</table>


<h2>Example 2:</h2>

- <b> M1:M2 = 1:1
- <b> L1:L2 = 1:2
- <b> Rod 1 Initial = pi/4 radians
- <b> Rod 2 Initial = pi/4 radians

<table>
<tr>
    <td><img src="https://i.imgur.com/7MpuDFZ.png" alt="Image 1" width="600" height="350"/></td>
    <td><img src="https://i.imgur.com/2hiE0zb.png" alt="Image 2" width="400" height="350"/></td>
</tr>
</table>
