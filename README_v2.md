
# 2024 I2P Mini Project 3 - Farm Battle
This is a two-player battle game that combines farming.  The purpose of the game is to kill the opponent player. Players need to grow vegetables to earn money, which can be used to obtain items in battle mode.  
we cut this game into three parts:  
  
**1.Game Scene  
2.FarmScene(our feature 1)  
3.Store Scene(our feature 2)**  

## 1. Game Scene
All roles have infinite amount of bombs, it can be put when the role has no tool.
Role can get tool by pass through the tool wrapped by bubble, and the tool would be used following FIFO.
 
| **Item**      |                           **Describe** <div style="width:200px">                            |                                                                   **attacking range** <div style="width:400px">                                                                    |
|:--------------|:-------------------------------------------------------------------------------------------:|:----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------:|
| Bomb          |                         explode after 3 seconds and keep 1 seconds                          | The exploding area of the bomb includes the square where the bomb itself is located,  <br/> as well as the squares directly in front, behind, to the left, and to the right of it. |
| Firearm       |                         explode right after shot and keep 3 seconds                         |                    The range of the flame attack extends from the second square ahead of the role's direction to the fourth square ahead, totaling three tiles.                    |
| Hammer        |             fully drop after 4second and only the forth seconds can attack role             |                                                      The hammer will drop in the three squares directly in front of the role.                                                      |
| ToolBomb      |                                make bomb's radius by 2 times                                |                                                                                         -                                                                                          |
| scarecrow     |                  block, need to be removed by FireEffect or firearmEffect                   |                                                                                         -                                                                                          |
| FireEffect    |                                        Bomb's Effect                                        |                                                                                         -                                                                                          |
| FirearmEffect |                                      Firearm's Effect                                       |                                                                                         -                                                                                          |
| HammerEffect  |                                       Hammer's Effect                                       |                                                                                         -                                                                                          |
| Role          | two roles,and their speed and live can be changed in the store, but the speed at least is 1 |                                                                                         -                                                                                          |


##  2. FarmScene  


This is a little farm game which you can earn money by harvest the crop you plant.  
While it is not just soley plant and harvest since you need to paid something to earn money.  
Firstly, as the saying goes, time is money. You need to stay at this farm so your plant can grow.  
Secondly, this game would challenge your "powers of recollection" !  
Because crops might change their image simultaneously, you need to remember their "harvest order" and follow it using a sickle to harvest you crops.  
If you succeed, the crop can be harvest and appears a "Up+1" image. Otherwise, the crop cannot be harvest.  
Also, It would change to crop's image from seed's image when it can be harvest.

| **Crop** | **CostTime** <div style="width:300px"> | **EarnMoney** <div style="width:300px"> |
|:---------------------------------|:--------------------------------------:|:---------------------------------------:|
| Wheat                            |                 10(s)                  |                   10                    |
| Vegetable                        |                 20(s)                  |                   20                    |
| Apple                            |                 40(s)                  |                   30                    |  
| Flower                           |                 60(s)                  |                   100                   |



## 3. Store Scene

This is the scene of the seed store and potion store, and here are the functionalities introduced:

|  **Functionality**  |                                **Describe**  <div style="width:700px">                                 |
|:-------------------:|:------------------------------------------------------------------------------------------------------:|
|    "Buy" button     |     Update the purchased quantity of seeds and update the remaining money to the file `money.txt`.     |
|  Seed number icon   | Update the number of purchased seeds that have not been planted. Remove the icon if no seeds are left. |
| The floating window |  Add `UI/Component/window.hpp/cpp`. Display product information when the cursor hovers over the icon.  |


##  Division of work table
|    **Name**     |   **Describe**  <div style="width:700px">   |
|:---------------:|:-------------------------------------------:|
| 羅敏華 (112062113) | Store Scene, audio editor, major art editor |
| 王友欐 (112062136) |        Farm Scene, minor art editor         |
| 蘇雨虹 (112062327) |        Game Scene, minor art editor         |



---

<style>
table th{
    width: 100%;
}
</style>
