# Robot_Dynamite
A first-person shooter using Unreal Engine 4

![Robot Dynamite Logo](Robot_Dynamite.png)



## Inventory System
### Startup

A BP_Character has a BP_Inventory component.
The BP_Inventory component starts up by calling its Create Slot method for each inventory slot available.  Slots are keyed by the name of the class of the item they contain.

As of 8/22/2017, the slots are BP_Melee, BP_Rifle, BP_GrenadeLauncher, BP_Health, BP_Armor, BP_KeyCopper, BP_KeySilver, BP_KeyGold, BP_LiftBelt, BP_NO2, and BP_NVG.

In addition to the class of the item, a slot contains an EitemType enum, whose value is one of Melee, Weapon, VitalStatistic (health and armor), Key, Powerup, or Ammo.
A slot can optionally be given a socket (on the actor mesh) to spawn, such as GripPoint for guns and Belt for LiftBelt and Eyes for NVG.
A slot takes a Boolean parameter: Spawn (bSpawn).  If checked (as it is for Health, Armor, Melee, and the first gun, Rifle), an item of the given class will be spawned (with the Spawn Inventory Item methdo of BP_Inventory) and a reference to it stored in the slot.
Then the BP_Character calls it’s own Select Inventory method on the BP_Rifle class to select the rifle as its starting gun.  Select Inventory calls BP_Inventory’s Get Item which returns the item (if it exists!) and a Boolean flag bIsValid.  It also returns the slot whether or not the item exists.   If it does not exist, the BP_Character’s Does Not Have event is fired (in the case of BP_RobotDynamite, the first-person player subclass of BP_Character, it displays a HUD message to the effect that the item does not exist.)  If it does exist, a switch statement on the EitemType calls the appropriate BP_Character method: Select Melee, Select Weapon, Select Power Up, etc.  If the item is successfully selected, it returns a bSuccess value of True, otherwise False.
The Select Melee method and the Select Weapon method stash whatever weapon is currently selected with the BP_Character method Stash Inventory, and then set the BP_Character’s variable Current Gun to the new weapon item.  In the case of Select Weapon, it also makes it visible, fires the On Weapon Select event of BP_Character, fires the On HUD Update event of BP_Character, and returns Success (if nothing went wrong).
The Select Power Up method only succeeds if you have the power up, and the “amount” is positive.  In that case, it sets the Current Power Up variable ofBP_Character to the power up, and fires the On HUD Update event of BP_Character.

### Pick Up

When a BP_Character overlaps the collider of a BP_Pickup, first BP_Pickup checks that it is active (it becomes inactive when the item is taken, and active again if it respawns the item).  If not, nothing happens.  Otherwise, BP_Character’s Get Item From Pickup method is called, and if successful (might fail if you already have item and it is fully loaded), a sound is played, bActive is unset, the Save Static Mesh variable of BP_Pickup is given the static mesh of the item, which in turn is set to SM_Invisible (since it was picked up!), and if the BP_Pickup’s Respawn Time variable is positive, it waits for that many seconds and then turns the item visible again by retrieving the mesh from Save Static Mesh, and bActive is set.
BP_Character’s Get Item From Pickup method takes the class of the item to get.  It calls BP_Inventory’s Get Item method (described in the previous section), and if valid (character already has the item), it calls the BP_Character’s Replenish Item From Pickup method, fires On HUD Update, and returns success if successful (fails if character’s item is maxed out in ammo/energy/whatever).  If not valid (character does not have the item), Spawn Inventory Item is called, and then On HUD Update is fired, and bSuccess is unconditionally returned True.
BP_Character’s Replenish Item From Pickup method switches on the EitemType of the slot it is given.  In case of a weapon, the BP_Reload method of BP_Weapon is called, then On HUD Update is fired.  If the weapon’s ammo amount changes due to reload (i.e. wasn’t already maxed out), bSuccess is true.
In the case of Melee, always returns failure since Melee cannot be refreshed by a pickup.
In the case of a VitalStatistic, if the current amount is below max, bSuccess is cached locally as True.  Unconditionally, the amount is set to max, On HUD Update is called, and bSuccess is returned. The case of PowerUp behaves the same.
Currently (8/22/2017) all other types return failure.

### Using Item

When the BP_Character uses an item, it calls Select Inventory on the item.
In the case of a weapon, the item is depleted when the character “fires” the weapon by calling the gun’s Trigger Pressed method.  In the case of a power up, the item is depleted by the character calling Use Up Lift Belt, Use Up Nitro, Run, etc. once per second.  In case of Health and Armor, the item is used up by  the character’s Event Any Damage  event.

With power ups, you can stop using them (and use more than one at the same time).  This stops the depletion.  This contrasts with a weapon in which only one can be used at a time, and it is used by “firing” it.
The Melee weapon is not replenished by a pickup.  Instead, it is replenished by “rest”--by one available hit every three seconds.
