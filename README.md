<a id="nola-overview"></a>

# NOLA Co-op · Stability 0.5

Play S.T.A.L.K.E.R. 2: Heart of Chornobyl with up to five players over Steam Friends or Direct IP. This unofficial fork is based on [NOLA v1.3.2 by Jaumn](https://github.com/Joaovitor404silva/NOLA-Stalker2-Coop).

**[Download the Windows installer](https://github.com/dreadnaughtgaming/NOLA-Stalker2-Coop/releases/download/v1.3.2-stability.0.5/NOLA-stability-0.5-v1.3.2-Installer.zip)** · [Release notes and source](https://github.com/dreadnaughtgaming/NOLA-Stalker2-Coop/releases/tag/v1.3.2-stability.0.5)

## Quick install

1. Close the game and extract the entire ZIP.
2. Run `install.bat` and choose **Steam Friends** or **Direct IP**. Everyone should install the same version.
3. Start the game. The host selects **Host co-op** and loads a save or starts a game. The others select **Join co-op**.

Built for the Steam version on Windows, game Update 2.1 (Steam build `26123434`). Stability 0.5 is an experimental prerelease. The installer was tested on Windows, and live multiplayer testing is pending.

## More information

<details>
<summary>Money transfer development preview</summary>

The `feature/player-money-transfer` branch adds transfers between the host and a guest. Look at the other player within about five metres, press INSERT, enter a whole amount and click Send in the Windows popup. The target is fixed when the popup opens. Both players need this preview build. Guest-to-guest transfers in larger sessions are not included yet.

The sender must have sufficient coupons. Each transfer is limited to 1,000,000 coupons, and balances must remain below 16,777,216 to keep the game's floating-point wallet API exact. Repeated packets cannot grant the same transfer twice. An explicit rejection returns the sender's money after verification.

The bridge directory contains `money-transactions.log`. Keep this journal. A missing acknowledgement, changed session/world/pawn, failed wallet verification or interrupted transaction blocks further sending. There is no automatic recovery for ambiguous outcomes, and save rollback can still undo wallet changes independently of the journal.

Windows DLL compilation, money regression tests and existing network/damage checks passed. Portable tests passed with AddressSanitizer and UndefinedBehaviorSanitizer (leak detection disabled because the test environment uses ptrace). A two-PC in-game test of selection, popup focus, balances and save/rejoin persistence is still required. The released stability 0.5 installer does not contain this preview.

</details>

<details>
<summary>Install help, FAQ, features and settings</summary>

<a id="nola-install"></a>

## Installation

**You need**
- The Steam version of S.T.A.L.K.E.R. 2: Heart of Chornobyl on Windows 10 or 11, Update 2.1 (Steam build 26123434). Other stores and other builds are not supported. A game update can break NOLA until it is updated.
- Every player on the same NOLA version.
- For Steam play: every player is a Steam friend of the host, with the Steam overlay on. For IP play: the PCs can reach each other on the same network or through a VPN.

**Quick start**
1. Close the game. Run the NOLA installer on every PC (it asks for administrator rights). Choose Steam friends or IP address.
2. Start the game. The main menu now has **Host co-op** and **Join co-op**.
3. The host picks Host co-op and then loads a world (Continue, Load or New Game).
4. The others pick Join co-op. With Steam, the host presses the Home key in the world to open the invite window. With IP, the joiner tries every host address typed at install until one answers.
5. To play solo, ignore both entries.

The installer keeps a backup of every file it replaces. Running it again lets you uninstall and puts everything back. It never touches your saves. The download contains full install notes.

---

---

<a id="nola-faq"></a>

## FAQ

**Is it safe for my saves?**
Co-op games use their own save slots and the installer does not modify your saves. Still, NOLA is not finished: back up your saves first.

**Do all players need the DLC?**
The mod was built and tested on the build that includes the Cost of Hope DLC. Setups without it have not been tested.

**Can I use it with other mods?**
NOLA ships its own copy of UE4SS. If you already use UE4SS mods, your own settings and mod list are kept and only the NOLA line is added. Other mods that change the same game data may clash, and this has not been tested.

**Why only the Steam version?**
Only the Steam build was used for development and testing.

**Is V1 final?**
V1 is out: v1.0, v1.1, v1.2.0 and v1.2.1 have been released. What comes next is in the [Roadmap](#nola-roadmap).

---

---

<a id="nola-features"></a>

## Features

Every row says honestly how far it has been checked.

| Status | Meaning |
|---|---|
| ✅ | Tested in game (live, with real game windows talking to each other) |
| 🧪 | Built, partly tested (some parts checked, or checked only on an earlier test build) |
| 🔧 | Built, not tested yet |
| ❌ | Off in this release |

"Tested" means tested by the author on test PCs, mostly with two players and a few shorter runs with three. It does not mean "proven for every mission in the game".

### Connecting

| Feature | What it does | Status |
|---|---|---|
| Host co-op / Join co-op in the main menu | Two new entries in the main menu. The host picks "Host co-op" and loads a world, the others pick "Join co-op". | ✅ |
| Connect by IP address (LAN or VPN) | Join a host on your local network, or through a VPN such as Radmin. This is what almost all testing used. | ✅ |
| Connect through Steam friends | The host opens a Steam lobby and invites a friend (overlay invite, Home key in the world). | 🧪 A Steam lobby join, leave and rejoin worked in a live test. |
| Up to 5 players | The host plus up to four friends. | 🧪 Two players tested a lot, three players tested in shorter runs (join, leave, rejoin, damage). Four and five players: not tested yet. |
| Join and land beside the host | A joining player is teleported next to the host as soon as the area around the host has loaded (about a second in the test, it used to take far longer). | ✅ |
| Leave and rejoin | When someone leaves, their body disappears for the others. When they come back there is still one body, not two. | ✅ |
| Switch between Host and Join in one session | You can go back to the menu and pick the other role without restarting the game. | ✅ |
| Solo play unchanged | Without pressing Host or Join, the game plays as normal. | 🧪 Checked on earlier test builds. |

### Shared world

| Feature | What it does | Status |
|---|---|---|
| NPCs and enemies from the host | The host runs the A-Life and the NPCs. Other players see and fight copies that follow the host's characters. | ✅ Cover animations on the copies were not perfect when last checked. |
| No invisible enemies for joiners | A joiner can no longer be attacked by enemies that exist only on their own PC and cannot be seen. | ✅ Verified in game logs (a screenshot proof was not possible). |
| NPC copies stop staring at dead targets | NPC copies on a joiner's PC no longer keep aiming at a body that is already dead. | ✅ Verified in game logs. |
| Mutants move and attack in step | Mutant speed, attack animations and the bloodsucker's cloak follow the host. | 🧪 Bloodsucker speed and the attack and cloak timing matched the host in measurements. Other mutant types, and how it looks, were not fully checked. |
| Time and weather follow the host | The joiner sees the same time of day and sky as the host. | 🧪 Worked in a live test on an earlier build. |
| Sleep together, no pause, emissions together | Sleeping needs everybody, one player cannot pause the game, emissions run for all. | 🧪 Checked on earlier test builds. Not re-checked in v1.2.0. |
| Doors, levers, breakable objects, anomalies | State changes made by one player are copied to the others. | 🧪 Checked on earlier test builds. Not re-checked in v1.2.0. |
| Padlocks and locked doors | A padlock one player breaks is broken for the other too, and the door behind it is no longer "locked" for them. | ✅ |
| Dropped items | An item one player drops lies on the ground for everybody, at the same place. Whoever picks it up first gets it, and it is gone for the others. | ✅ The case where two players grab it in the same instant was only tested offline. |
| Dead bodies and loot | One body per death, in the same place for everybody. Loot it from any player. A looted body stays where it is, with nothing left to take. | ✅ |
| Stashes and containers | Stashes open normally for every player (a bug that closed the box by itself was fixed). | ✅ |
| Traders | In V1 each player sees their own trader stock. | 🧪 By design for now. Shared stock is planned. |

### Story and quests

| Feature | What it does | Status |
|---|---|---|
| Quest progress follows the host | Everybody's journal shows the same mission and objectives as the host's. | ✅ Checked in the opening story missions, not through the whole game. |
| Quest items for everybody | A quest item picked up by one player is given to the other players too, once, with no duplicates after reloading or reconnecting. | ✅ |
| Host chooses story branches | In decisive dialogue, only the host picks the answer. A joiner who clicks one gets a short notice and then follows the host's choice, so nobody ends up on a different path. | 🧪 Checked on one radio conversation and one random branch. The large table of other branches is built but was not checked one by one. |
| Catch-up for a lagging player | If one player is behind in a mission, the missing steps are completed for them after a short wait. | 🧪 Tested for a joiner who was behind the host. |
| Cutscenes and scenes together | Everybody is brought to the scene together. | 🧪 Worked in a live test on an earlier build. |
| Fast travel together | Guide travel is meant to take everybody along. | 🔧 |

### Your character

| Feature | What it does | Status |
|---|---|---|
| Each player keeps their own character | A joiner keeps their own gear, condition, attachments, quick slots and health. The host's world is merged with the joiner's character when they join. | ✅ |
| Co-op has its own save slots | Co-op games are saved in a separate place, so your normal solo saves are not touched. The co-op slots start empty. | ✅ |
| Weapon upgrades | Weapon upgrades on your items after a join or reload. | 🔧 Not verified. See Known issues. |
| Worn gear on rejoin | A joiner's game, with their worn gear, is saved when they exit or disconnect, so it comes back when they join again. | ✅ |

### Your partner's character (v1.2)

| Feature | What it does | Status |
|---|---|---|
| Friends on the compass | Each other player shows as a marker on your HUD compass at any distance and follows them. | ✅ |
| Aim, lower, safe zones | Aiming pose for rifles and pistols, H lowers the weapon, weapon hidden in safe zones. | ✅ |
| Shooting | The game's own fire animation per weapon, on body and gun; the Mosin cycles its bolt. | ✅ |
| Reloads | Rifles, shotguns, SVD, PKP and pistols reload with the weapon in the hands. | ✅ |
| Pistol, knife, bolt, detector | Proper grips; detector in the left hand, bolt in the right. | ✅ |
| Movement | Lean, crouch transitions, vaulting, ladder climbing, feet planted when standing still. | ✅ No crouch-walk animation (the game has none for other characters). |
| Stashes and bodies | Crouches and searches for as long as a stash is open; body search animation. | ✅ |
| Grenade throw on the partner | The throw motion seen on the partner. | 🔧 Not yet tested in a live session. |

### Combat and survival

| Feature | What it does | Status |
|---|---|---|
| Joiner damages enemies | A joiner's bullets and knife hurt the host's enemies, once per hit. | ✅ |
| Joiner grenades | A joiner's grenade damages the host's enemies. | 🧪 Worked in a live test, checked in game logs only. |
| Enemies hurt every player | Enemy damage reaches joiners as well as the host. | ✅ |
| Friendly fire | Players can hurt each other, in both directions (host to joiner and joiner to host). On in V1. | ✅ |
| Downed, bleed-out and revive | At low health you drop to the ground with the camera low and no weapon in your hands, and you bleed out in about 30 seconds. A teammate stands close and holds F with a medkit to get you up, and the medkit's healing is applied to you. | ✅ |
| Everybody down means game over | If all players are downed or dead, it is game over and the game reloads, like in the stock game. | ✅ |
| Real cause on the death screen | A co-op death shows the real cause of death (or the game's default text) instead of always "shot". New in v1.2.0. | ✅ |

### Loading and sessions

| Feature | What it does | Status |
|---|---|---|
| Load together | A joiner waits on the loading screen until the host's world is up. When the host loads, reloads, or reloads after a death, the joiner follows. | ✅ |
| "Corrupt save" popup fixed | Starting Host co-op and then Continue no longer shows a false "file is corrupted" message. The host popup also tells you to pick Load or New Game when the co-op slots are empty. | ✅ |
| Session messages | A small box in the game's own tutorial style tells you when somebody joins, leaves or loses the connection. English, Portuguese and Spanish, following the game's text language. | ✅ |
| Back to the main menu when the host goes silent | If the host disappears for long enough, the joiner is taken back to the main menu. | 🔧 Not tested in game. |

### Menu and look

| Feature | What it does | Status |
|---|---|---|
| NOLA logo in the main menu | A small NOLA logo sits next to the game's logo, in the bottom corner beside the Cost of Hope badge. | ✅ |
| Menu texts in three languages | Host / Join entries and popups in English, Portuguese and Spanish. | ✅ |

### Turned off in this release

| Feature | What it would do | Status |
|---|---|---|
| NPC copy parking | Park distant NPC copies out of the way to save performance. | ❌ It failed in testing. A fix exists but has not been tested, so it is left off. |

---

---

<a id="nola-flags"></a>

## Settings and flags

NOLA keeps its settings in one small text file. You can open it, switch features off, or change a few numbers (like how long you can bleed out). This page explains the settings that are safe and useful for players.

You never have to touch this file to play. The defaults are the ones NOLA was tested with.

### The settings file

- **Where it is:** `C:\nola_bridge\flags.txt` (this is the default install location).
- **How to edit it:**
  1. Close the game.
  2. Open `flags.txt` in Notepad.
  3. Change the value after the `=`, for example `friendlyfire=1` becomes `friendlyfire=0`.
  4. Save the file and start the game.
- **Format:** one `key=value` per line, no spaces and no quotes.
- **Values:** most settings are **1 = on** and **0 = off**. Some are numbers (seconds, a scale, a distance) or a word (like `steam` or `ip`).
- **Make a backup first.** Copy `flags.txt` to something like `flags_backup.txt` before you change anything. If something goes wrong you can copy it back.
- **Only change the lines on this page.** The file has many more lines. They are tuning values that the mod needs exactly as they are, so please leave them alone.
- **The installer rewrites the file.** If you run `NOLA-Setup.exe` again (reinstall or update), your changes are replaced by the defaults, and the connection lines (`net` and `netpeer`) are written again from your answers. Keep your backup and copy your changes back afterwards.

### Do all players need the same settings?

Mostly it does not matter, because **the host decides**. These settings are sent from the host to everyone who joins, and they **follow the host automatically** while you are in the host's game. They are marked with 🔗 in the tables below. Your own value comes back when you leave the session. So for a 🔗 setting you only need to change it on the **host's** PC.

For the settings without 🔗, each PC uses its own file. Most of them only matter on one side (for example the connection lines are for the player who joins by IP). If you are not sure, the simplest safe rule is: **everybody uses the same file and the same NOLA version.**

For this to work, `hostcfg` must stay on (see "Don't change" below).

### Connecting

| Setting | Default | What it does | What happens if you turn it off |
|---|---|---|---|
| `net` | `steam` | How the PCs connect: `steam` (Steam friends) or `ip` (LAN, or a VPN such as Radmin). The installer writes this line for you. | Not an on/off switch. Change it to `ip` to play by IP address, or back to `steam` for Steam friends. |
| `netpeer` | your answer in the installer | IP play only: the IP addresses of the PCs that may host, separated by commas, for example `192.168.0.10,192.168.0.11,26.1.2.3`. Join co-op tries each one until a host answers; Host co-op ignores it, so every player can use the same list. Not used with Steam. The installer writes this line for you. | Not an on/off switch. One address works too. |
| `maxclients` | `4` | How many other players the host accepts. The host plus 4 joiners is 5 players in total. | Use a smaller number for a smaller session. For example `2` means the host plus 2 friends. 4 is the most. |
| `steaminvite` | `1` | Steam only: when you start hosting, the Steam invite window opens by itself so you can pick friends. | You open the invite window yourself by pressing **Home** in the world. |
| `steamjoin` | `1` | Steam only: "Join co-op" looks for your Steam friends' hosted games. | "Join co-op" no longer finds Steam hosts. Leave this on if you use Steam. |
| `joinport` | `1` | When you join, you are moved next to the host. | You stay where your own game loaded you, maybe far from the host. |
| `joinm` | `10` | Distance in metres. If you are already closer to the host than this when you join, you are not moved. | A bigger number means you are moved less often. A smaller number moves you even when you are quite close. |
| `cpp_port`, `cpp_net`, `cpp_session`, `cpp_world`, `cpp_npc`, `cpp_pop`, `cpp_items`, `cpp_bodies`, `cpp_damage`, `cpp_lock`, `cpp_quest`, `cpp_save`, `cpp_travel` | `1` | ⚠️ **Don't change.** These switch on the parts of the mod that do the real work (the connection, the shared world, NPCs, items, damage, quests, saves, travel). | Co-op stops working or breaks in strange ways. |
| `natnpc` | `1` | ⚠️ **Don't change.** This is how the host's NPCs and enemies appear and move on the joiners' PCs. | Joiners no longer see the host's NPCs and enemies properly. |
| `hostcfg` | `1` | ⚠️ **Don't change.** This is the thing that sends the host's settings (the 🔗 ones) to the joiners. | Joiners keep their own values, so the game can play differently for each player. |
| `joinmenu` | `1` | ⚠️ **Don't change.** The "Host co-op" and "Join co-op" entries in the main menu. | You can no longer start or join a co-op game from the menu. |
| `menurole` | `1` | ⚠️ **Don't change.** Makes the game remember if you picked Host or Join, so it behaves the right way for that role. | The game can behave as the wrong role, and co-op breaks. |

### Shared world

| Setting | Default | What it does | What happens if you turn it off |
|---|---|---|---|
| `doors` 🔗 | `1` | When one player opens or closes a door, it moves for the others too. | Doors are no longer copied. Each player sees their own door state. |
| `lockbrk` 🔗 | `1` | A padlock that one player breaks is broken for the others too. | Each player has to break the padlock themselves. |
| `dobj` 🔗 | `1` | Breakable objects (props you can smash) that one player breaks are broken for the others too. | Smashed objects are not copied. Each player sees them broken only on the PC where they were smashed. (This works together with `dobjgen`, which also needs to stay `1`.) |
| `ien` 🔗 | `1` | Switches, levers and other things you can use are copied between players. | They are no longer copied, so one player can switch something and the others do not see it. |
| `anomsync` 🔗 | `1` | When a player triggers an anomaly, it also goes off for the other player. | Anomalies only react to the players on the PC where they are. |
| `idrop` 🔗 | `1` | An item that one player drops on the ground lies on the ground for everybody. | Dropped items stay only on your own PC. |
| `ground` 🔗 | `1` | When one player picks up an item lying on the ground, it disappears for the other players. | The same item can be picked up again by the other player. |
| `lootshare` 🔗 | `1` | A dead body has one shared list of loot, so every player sees the same items on it. | Each player can see a different list on the same body. |
| `emsync` 🔗 | `1` | Emissions follow the host. | Each PC runs its own emission schedule. |
| `wxfollow` | `1` | Joiners: when the host's weather changes, yours changes to match. | Your weather can be different from the host's. |
| `nopause` 🔗 | `1` | Opening the pause menu does not freeze the game, so nobody can stop the world for everybody else. | The game pauses on your PC when you open the menu, like in solo play. |
| `sleepsync` 🔗 | `1` | When one player goes to sleep, the other goes along. If the other player refuses or does not answer, the sleeper is put back. | Each player sleeps on their own. |
| `sleepmode` 🔗 | `1` | How the other player goes to sleep. `1` = at once. `2` = they must lie down in a bed themselves (they get a short time to do it). | Not an on/off switch. Only `1` and `2` mean something. |
| `wshot` | `1` | The host sends NPC gunshots to the joiners. | Joiners do not get those shots. |
| `wvoice` | `1` | NPC voice lines are sent to the joiners and played there. | Joiners do not hear those voices. |
| `wsfx` | `1` | Joiners: the relayed NPC shots and voices are played on your PC, with the gun sound and a muzzle flash. `2` also adds the bullet trace. | You do not hear or see them. |

### Story and quests

| Setting | Default | What it does | What happens if you turn it off |
|---|---|---|---|
| `qsync` 🔗 | `1` | ⚠️ Quest progress follows the host. Everybody's journal shows the host's mission. Other quest settings depend on this one. | Each player's quests go their own way, and the other quest features stop making sense. I would not turn it off. |
| `choice` 🔗 | `1` | Story choices stay with the host. A joiner who tries one is stopped and follows the host's choice, so nobody ends up on another path. | Joiners can make story choices that the host did not pick, and the players can split onto different paths. |
| `lead` 🔗 | `1` | ⚠️ When one player starts a story conversation or scene, the other player follows it and cannot start a different story conversation at the same time. | Both players can start story conversations at the same time, which can leave the story in different places. |
| `ldblk` 🔗 | `1` | While one player is in a story conversation, the other player cannot talk to people nearby. Traders stay free. Needs `lead=1`. | The other player can talk to other people during your conversation. |
| `qcatch` | `1` | If one player is behind in a mission, the missing steps are completed for them after a short wait. | A player who is behind stays behind. |
| `qshare` 🔗 | `1` | A quest item picked up by one player is given to the other players too (once, no copies). | Only the player who picked it up gets the quest item. |
| `qdrop` | `1` | Drop a quest item by holding **D** on it in the inventory. | You cannot drop quest items. |
| `cine` 🔗 | `1` | The host's cutscenes and scenes are announced to everyone. Friendly fire is also paused during a cutscene. | Joiners are not told about the host's scenes. |
| `cjoin` 🔗 | `1` | Before a story scene starts, a player who is far away is moved next to the other player (far means more than about 15 m). | Players who are far apart stay where they are when the scene starts. |
| `ftfollow` 🔗 | `1` | When one player uses a guide's fast travel, the other is taken along. **Not tested in game yet**, see [Features](#nola-features). | Each player fast travels on their own. |

### Your character

| Setting | Default | What it does | What happens if you turn it off |
|---|---|---|---|
| `coopsaves` | `1` | ⚠️ Co-op games are saved in their own place, so your normal solo saves are not touched. | Co-op would use your normal save slots, so a co-op game can end up mixed with your solo saves. Please don't. |
| `csave`, `csmenu`, `csexit`, `cswc` | `1` | ⚠️ **Don't change.** Part of the co-op save system, and the fix for the false "corrupt save" popup. | Saving in co-op can go wrong, and the false "file is corrupted" popup can come back. |
| `n7` 🔗 | `1` | ⚠️ **Don't change.** This is how a joiner keeps their own character (gear, health, quick slots) in the host's world. | Joiners may not keep their own character. |
| `sxjoin`, `wsplice`, `wspair`, `wstrip`, `wspos`, `wpkg` | `1` | ⚠️ **Don't change.** These put the joiner's character into the host's world when they join. | Joining can fail or leave you with the wrong character. |

### Combat and survival

| Setting | Default | What it does | What happens if you turn it off |
|---|---|---|---|
| `friendlyfire` 🔗 | `1` | Players can hurt each other, both ways (host to joiner and joiner to host). | Players cannot hurt each other. |
| `ffscale` 🔗 | `1.0` | How strong friendly fire is. `1.0` = full damage, `0.5` = half, `2.0` = double. | `0` = no damage between players (the same as `friendlyfire=0`). |
| `dmgin` | `1` | A joiner's bullets hurt the host's enemies. | A joiner's bullets stop hurting enemies. |
| `meleesync` | `1` | A joiner's knife and melee hits hurt the host's enemies. | A joiner's melee hits stop hurting enemies. |
| `lifeguard` 🔗 | `1` | ⚠️ The "downed" system. At low health you drop to the ground instead of dying, and a teammate can pick you up. | There is no downed state, you die in the normal way. Friendly fire and the other downed settings below stop working. |
| `downhp` 🔗 | `15` | The health level at which you go down. | Not a switch. A lower number means you have to be closer to death before you go down. |
| `downsecs` 🔗 | `30` | How many seconds you can stay down (the bleed-out time). | Not a switch. A bigger number gives your friends more time. |
| `downdie` 🔗 | `1` | When `downsecs` runs out, you die. | With `0`, you stand up on your own after `downsecs` instead of dying. |
| `reviveitem` 🔗 | `1` | A teammate stands close, holds **F** with a medkit, and you get up. | With `0`, a teammate only has to stand close to you for `revivesecs` seconds, with no medkit needed. |
| `reviveradius` 🔗 | `300` | How close the helper must be, in centimetres. `300` is about 3 metres. | Not a switch. A bigger number lets the helper stand farther away. |
| `revivesecs` 🔗 | `3` | Used only when `reviveitem=0`: how many seconds the helper must stand close. | Does nothing while `reviveitem=1`. |
| `revivehp` 🔗 | `30` | The health you get back when you stand up. | Not a switch. A bigger number means you stand up healthier. (If `reviveheal=1`, the medkit's own healing is used instead.) |
| `reviveheal` 🔗 | `1` | The healing of the medkit your friend used is applied to you when you get up. | You get up with `revivehp` health instead. |
| `downnoweap` | `1` | While you are down, you have no weapon in your hands. | You keep your weapon in your hands while down. |
| `downcam` | `1` | While you are down, the camera is low, near the ground. | The camera stays at the normal height. |
| `bothdie` 🔗 | `1` | ⚠️ If one player dies, or all players are down, the others die too and the game goes back to the last save. This is the "everybody down means game over" rule. | A death does not drag the other players down with it. |
| `bothdown` 🔗 | `1` | When all players are down at the same time, it is game over at once (without waiting for the bleed-out). Needs `bothdie=1`. | Downed players keep bleeding until their own time runs out. |
| `dieload` 🔗 | `1` | Joiners: if you die, the "load save" buttons on the death screen are blocked. Only the host loads, and everybody follows. | Joiners can click "load" on their own death screen. |

### Loading and sessions

| Setting | Default | What it does | What happens if you turn it off |
|---|---|---|---|
| `lsgate`, `lshold` | `1` | ⚠️ **Don't change.** A joiner waits on the loading screen until the host's world is ready. | The joiner no longer waits for the host's world, and joining can go wrong. |
| `uitut` | `1` | NOLA's session messages (someone joined, someone left, connection lost) show in the game's tutorial-style box. | The messages stop using that box. |

### Menu and look

| Setting | Default | What it does | What happens if you turn it off |
|---|---|---|---|
| `nolatitle` | `1` | The small NOLA logo in the main menu. | The logo is hidden. |
| `nolatitleimg` | `1` | The picture of the logo. | The logo is hidden (same as `nolatitle=0`). |

### If something goes wrong

- **Put your backup back.** Close the game and copy your `flags_backup.txt` over `flags.txt`.
- **Or reinstall.** Run `NOLA-Setup.exe` again. It writes a fresh `flags.txt` with the defaults. Your saves are not touched.
- **Still stuck?** [Open an issue](https://github.com/Joaovitor404silva/NOLA-Stalker2-Coop/issues/new) and tell us which line you changed. Please see the [README](#nola-overview) for what to include.

---

---

<a id="nola-known-issues"></a>

## Known issues

- **Game patch:** v1.3.2 needs the STALKER 2 patch Update 2.1 (Steam build 26123434). On older game builds use v1.2.0; on newer builds the co-op entries may be missing until NOLA is updated.

- **Items a joiner picked up after the host's last save** come back as fresh items without their upgrades when the host reloads.
- **Weapon upgrades** carry over when items are put into a box or dropped (v1.1). A joiner's money and items are kept on rejoin (v1.3.0), but upgrades have not been verified after a join or reload.
- **NPC animations** on a joiner's screen sometimes reset or stutter (better in v1.3.0, not fixed).
- **Compass:** nearby enemies get no direction marker on the compass (not fixed yet).
- **One huge hit** (for example a grenade at close range) can kill a joiner outright, without the downed state.
- **The host going silent** is not tested in game, so what a joiner sees then may not be right yet.
- **Running enemies and mutants:** on a joiner's PC the legs now follow the body more often, but fast running can still slide a little, and dogs less well than humans.
- **An extra body** of another player can sometimes be seen after a very long jump (a long teleport).
- **Messages:** the NOLA message box borrows the game's tutorial box, so a game tutorial hint can replace a NOLA message.
- **Quitting the game while Steam is running** used to crash the game on exit (no data is lost). A fix has been included since v1.0 but has not been confirmed in game yet.
- **Dead bodies:** a body that was already emptied before the host reloaded can become lootable again after the reload.
- **Cover:** enemies in cover show the cover animation in most checks, but can stand up for a moment when they change cover.
- **Dead enemies:** about 1 in 8 dead enemies lay upright on a joiner's screen in a test.
- **First mission:** the cave fire, a few journal lines and a sound from the host's story do not reach the joiner.
- **Graphics settings:** if a joiner's hair or object detail setting is lower than the host's, enemies look coarser on that PC. Set them the same.
- **Dropped items:** after a host reload, an item restored on the ground can be removed again by a later save and load.
- **Not yet checked live in v1.3.0:** host-only story quests, neutral enemy copies, wounded enemy sync and the bar cutscene dialog (see the changelog).
- **No crouch-walk animation** on the partner: the game has none for other characters, so a crouched partner slides along with still legs.
- **Throwing the bolt** on the partner uses the rifle grenade-throw motion.
- **Grenade throw on the partner** has not been tested in a live session yet.
- **Movement smoothing over the Steam relay** is in, but the remaining delay there was not measured (testing used LAN).
- **Four or five players and long play sessions** have not had proper testing yet.

If something breaks, please say what you were doing. Back up your saves before you try it.

</details>

<details>
<summary>Changelog and roadmap</summary>

<a id="nola-changelog"></a>

## Changelog

### Unofficial stability 0.5 — cumulative fork changes (2026-11-06)

This section describes **all cumulative custom changes in stability 0.5 compared with original NOLA v1.3.2**, not just changes since our previous installer. The upstream baseline is commit `9485e81a875e67981a8ecb92289c81eed47d3597`; the published custom build is commit `8694d062a32f2fd132f53792dc1108d357fccf52`, tagged `v1.3.2-stability.0.5`.

NOLA was created by **Joaovitor404silva (Jaumn)** and its contributors. This unofficial fork retains their authorship, history and GPL-3.0 licensing. Custom changes were prepared for dreadnaughtgaming with assistance from OpenAI Codex.

[Download the installer and matching source](https://github.com/dreadnaughtgaming/NOLA-Stalker2-Coop/releases/tag/v1.3.2-stability.0.5). All players should use the same patched build. **Windows compilation and automated tests passed; live co-op validation remains pending.**

#### Downed players and notifications

- Removed native timed bleed-out and timed automatic stand-up. Downed players wait for revival or the existing all-players-down team wipe; normal revive range and medkit requirements remain.
- Legacy `downsecs` / `downdie` configuration keys no longer control a native downed timer. This does not prevent exceptional engine instant-death paths or change actual-death propagation.
- Replaced upstream's downed countdown with a persistent waiting-for-revival message and HOME rescue instructions.
- Added fresh-transition teammate-down alerts, including at a distance, without repeating every tick or after brief stale-update gaps. Labels are `HOST` / `PLAYER n`, not Steam display names.
- Retained upstream's nearby F/medkit prompt and revived-by message, displayed after the downed camera releases. Added or retained feedback for missing medkits, pending requests, stale teammate updates, confirmed refunds and unresolved transactions.

#### HOME rescue / unstuck action

- While downed, hold HOME continuously for **five seconds** to move beside the nearest eligible standing teammate, selected by 3D distance.
- An on-screen countdown explains that the player will be moved. Releasing early cancels the action and clears the countdown. This rescue countdown remains; the death countdown does not.
- Excludes stale, disconnected and downed targets. Rescue is disabled while standing, during a team wipe and during blocked cinematics; the game window must have focus.
- Tries eight collision-checked positions approximately 1.2 metres around the target at the reported height. If all fail, the player stays in place; there is no unchecked position-setting fallback.
- Rescue preserves the downed state and does not heal, revive or spend a medkit. Release HOME to rearm; successful rescues have a ten-second cooldown. Result, blocked-target and cooldown messages explain the outcome.
- Suppresses the Steam invitation HOME shortcut while downed; it remains available while standing. Rescue messages receive higher UI priority through the existing NOLA message system.
- Collision checks do **not** guarantee an anomaly-free destination, safe floor or loaded destination area.

#### Revive requests and medkit handling

- Holding F no longer spends another medkit every five seconds: a new key press requires release first.
- Pending requests can briefly wait for a fresh teammate update, with a bounded extra wait of three seconds. A changed rescuer session invalidates the request.
- Medkit removal is invoked directly rather than treating insertion into an item-removal queue as a successful debit. The inventory count must fall by exactly one before a revive is sent.
- Delayed removal is observed without issuing a second removal. After ten seconds an unconfirmed debit becomes unresolved and cannot turn into a late revive request.
- With receipt-capable peers, permits only one local medkit transaction at a time and blocks further F attempts until its result is resolved.
- Adds request identity (`RT`) and receipt (`RA`) tags. Receipt handling checks the recipient view, peer identity/session, request counter, target player and process-lifetime nonce. Duplicate or mismatched replies cannot trigger another refund.
- An **explicit rejection** can return one medkit of the original type; the inventory increase is checked. A possibly successful grant is never retried automatically.
- Competing rescuers no longer replace the first active request or reset its application timer. Terminal receipts are retained per view for retransmission.
- Sends rejection when the recipient is already standing, dead, without a pawn, has the life guard disabled, or is in the all-down wipe path.
- Missing acknowledgements are **not** treated as rejection. Session/pawn changes and unconfirmed debits/refunds leave the transaction unresolved, show a message and block further medkit transactions for the current module lifetime.
- Refunds require support on both sides. Older peers, or attempts before receipt capability metadata arrives, use the legacy path without refund acknowledgements. There is no durable journal or automatic recovery across disconnects, crashes, reloads or save rollback. Concurrent inventory changes can interfere with count-based verification.

#### Networking and player synchronization

- Caps expanded network JSON at **1 MiB**. All decompressor output paths enforce the caller's budget, including literals and stored blocks; generic non-network decoding retains its previous 64 MiB default.
- Direct/non-hub UDP rejects gameplay, control and save packets from endpoints other than the configured peer. Discovery and hub admission remain separate. This is endpoint validation, not cryptographic authentication.
- Prevents retired session headers and NPC updates from replacing the accepted session; unknown NPC sessions cannot replace current NPC records. Retired-session history is bounded to 256 transitions and resets when the relay restarts.
- Resets sender delta caches when the local session changes, allowing the new session to resend needed state.
- Limits receive work to 256 packets or four milliseconds between packets per iteration. A single packet may take longer, so this is not a hard real-time deadline.
- Fixes the receiver's shadowed assigned-player-ID variable that could reject forwarded teammate snapshots and hide a third player. Invalid roster slots remain rejected; forwarding, self-exclusion and slot reassignment have regression coverage.

#### Guest traders, technicians and dialogue locks

These are fixes to existing guest interaction paths, **not a claim that guest trading was previously impossible**.

- Failed NPC interaction restores remain pending for retry; failed disables are not recorded as successful.
- Previously blocked traders are restored when recognised later. Population vendor identity also exempts recognised traders from the dialogue lock, and held dialogue checks are refreshed as actor data arrives.
- Enables `vendtrade=1` by default for the guest role. An explicit existing `vendtrade=0` still overrides that default. Recognised traders use the existing native trade-opening path; technicians use upgrades. Host dialogue behaviour is preserved.
- Uses the interacted actor's population vendor metadata instead of relying only on the narrower vendor-reference-position radius. Matching still depends on the vendor table and nearest-actor recognition.
- Waits up to two seconds for late vendor identification; closing dialogue resets the wait.
- Prevents host-controlled story scenes from triggering automatic guest trade opening, and restores hidden dialogue answers when the native trade call fails.
- Does not broadly unlock story NPCs, give guests host quest authority, add shared merchant-stock transactions, or guarantee a fix when no interaction prompt/dialogue view appears.

#### Doors and menu stability

- Failed native door lock/unlock operations remain pending with retry backoff. Only verified successful state is cached as applied. An unloaded/missing door is not marked applied when retries expire, allowing a later fresh update to retry.
- Adds generation checks to asynchronous menu transitions. Older callbacks are cancelled after a newer toggle, session end, world entry or view destruction, including save waits, animation waits and delayed popups.
- Combines those checks with upstream v1.3.2's toggle gate; cancelled current transitions and popup-free completions release the gate.

#### Upstream v1.3.2 fixes included — credit to the original project

These are inherited baseline features, **not additional fixes authored by this fork**:

- Close-behind doors/areas wait for the group (upstream issue #29).
- Grenade-tripwire disarm uses deactivation instead of damage replay (#37).
- Synthetic per-view compass marker IDs and visibility/fade fixes (#22).
- Menu toggle gating and animation completion waits (#21).
- Downed/revive UI and revived-by feedback (#20), adapted here to remove the death countdown.

The upstream compass implementation replaced our earlier marker-removal-order fix. That earlier fix is not a separate feature in the current build. Our door-state retries and menu callback cancellation remain alongside upstream's fixes because they address different failure paths.

#### Build, packaging and validation

- CMake accepts `UE4SS_ROOT` instead of requiring the original author's drive layout. `BUILD_PATCH.ps1` runs native network/damage tests and builds the release DLL against a supplied RE-UE4SS checkout.
- Corrected a literal carriage return and Windows-only data paths in the damage test harness; added production-logic regression scenarios for the changes above, plus upstream merge checks.
- Published a clearly labelled unofficial experimental installer and corresponding source. Retains the upstream v1.3.2 runtime/game-data payload and updates the patched DLL's installer checksum.
- Windows DLL build and native regression tests passed on 2026-11-06. Steam install, IP reinstall and uninstall passed in an isolated test folder; original files were restored byte-for-byte. This was not an automatic installation into the actual game.
- Portable tests cover network budgets/session handling, roster forwarding, downed state through ten minutes and late revival, all-down wipe, HOME rescue, revive receipts, vendor recovery, menu cancellation and door retries. AddressSanitizer/UndefinedBehaviorSanitizer were used where supported; game calls are mocked. Merge checks also cover close-behind logic, table/text consistency and trap-disarm replay. The optional real ZoneKit quest-file generator check was skipped because those external files were unavailable.
- These tests do not establish live transport behaviour, every NPC interaction, collision/anomaly safety, or four/five-player and long-session stability. See [Windows validation](validation/WINDOWS_0.5.log).

#### Still unfinished / not claimed fixed

- Player-to-player money transfer, including looking at a player and pressing INSERT for an amount/Send interface.
- Durable revive transaction recovery after disconnect, crash, reload or save rollback.
- Remaining guest dialogue failures without a prompt; join crash (#31); moving electrical/fire anomalies (#30 and anomaly-related #25); quest reports (#27); radiation-on-load reports (#23).
- Proposed new fragmentation/reassembly and protocol negotiation, authenticated session handshakes, adaptive smoothing, general reliable-event acknowledgements, world reconciliation/late-join snapshots, further item/upgrade/save persistence repairs, NPC lifecycle redesign, traffic prioritisation and a new connection UI. These were discussed but were not added by this fork; this does not imply upstream lacks all related mechanisms.

#### Custom version history

| Custom version | Main additions |
| --- | --- |
| 0.1 | Unlimited downed time, five-second HOME rescue, initial network hardening and portable build/test support, initially based on upstream v1.3.1. |
| 0.2 | Third-player forwarding fix; interaction restore, menu and door retries; revive feedback, held-F protection and stale/session checks. |
| 0.3 | Guest trader/technician default, metadata-based recognition, late recognition wait and failed trade-call recovery. |
| 0.4 | Merged upstream v1.3.2 while keeping unlimited downed time and HOME rescue; adapted notifications and reconciled overlapping fixes. |
| 0.5 | Verified revive medkit debit, explicit rejection receipts/refunds, duplicate protection and competing-rescuer handling; Windows installer/source release. |

The original checkpoint notes for versions 0.1–0.5 are available in [repository history](https://github.com/dreadnaughtgaming/NOLA-Stalker2-Coop/tree/ffcd0fa3491943b7a70cdb2da9464ae53f7fa15b). Use this changelog and the Windows validation record for the status of the published build.

### Original upstream release history

The entries below retain the original author's changelog. In particular, the upstream v1.3.2 countdown description does **not** describe this fork's unlimited-downed behaviour.

### v1.3.2 (2026-11-04)

Fixes five reported bugs. Same game build as v1.3.1 (Update 2.1, Steam build 26123434). Every player must install the same version.

#### Fixed
- **Guest locked out behind code doors:** when the host entered a door code (for example 2605 in Nestor's quest) and walked through, the door closed behind the host and the guest could not open it. Doors and areas that close behind the player now stay open until every player is inside, for every such door in the game. ([issue #29](https://github.com/Joaovitor404silva/NOLA-Stalker2-Coop/issues/29))
- **Guest dies after disarming the mill grenade trap:** disarming a tripwire grenade in the old mill set the grenade off on the host's side. Disarming now works the same for everyone. ([issue #37](https://github.com/Joaovitor404silva/NOLA-Stalker2-Coop/issues/37))
- **Partner icon disappears from the compass:** the partner icon no longer vanishes and comes back, near or far. ([issue #22](https://github.com/Joaovitor404silva/NOLA-Stalker2-Coop/issues/22))
- **Main menu stops responding after toggling co-op:** switching co-op on, off and on again quickly no longer freezes the menu. ([issue #21](https://github.com/Joaovitor404silva/NOLA-Stalker2-Coop/issues/21))
- **No information when a partner is down:** a downed player sees a countdown, the partner sees "Press F to revive (uses a medkit)", and everyone sees who revived whom. ([issue #20](https://github.com/Joaovitor404silva/NOLA-Stalker2-Coop/issues/20))

### v1.3.1 (2026-11-01)

Fixes [issue #18](https://github.com/Joaovitor404silva/NOLA-Stalker2-Coop/issues/18) and lost loot, and makes IP play easier for groups. Same game build as v1.3.0 (Update 2.1, Steam build 26123434). Every player must install the same version.

#### Fixed
- **Joiner always hungry and sleepy:** when the joiner's game clock was ahead of the host's, the clock sync set it back, the game counted a whole day passing, and hunger and sleepiness filled up again right after eating or sleeping. The sync no longer moves the clock back. ([issue #18](https://github.com/Joaovitor404silva/NOLA-Stalker2-Coop/issues/18))
- **Items next to a picked-up item vanished:** picking up one item could hide an identical item lying close to it, for every player. Now only the item you took is removed. Fix by Sternab.

#### New
- **IP play with several PCs:** the installer asks for the IP address of every PC that may host, separated by commas. Every player can type the same list, their own address included. Join co-op tries each address until a host answers; Host co-op ignores the list. See `netpeer` in [Flags](#nola-flags).

#### Removed
- The `devdlc` developer switch. NOLA never touches DLC ownership: every player needs their own copy of the game and of every DLC the host uses.

### v1.3.0 (2026-10-31)

This update is about the enemies, mutants and bodies a joiner sees, and about not losing things. It also fixes parts of [issue #16](https://github.com/Joaovitor404silva/NOLA-Stalker2-Coop/issues/16). The game build stays Update 2.1 (Steam build 26123434). Every player must install the same version.

#### Fixed
##### Your character, saves and items
- **Rejoin keeps money and items:** A joiner who leaves and joins again now keeps their money and items on saves made by game patch 2.1. Before, every 2.1 save fell back to a basic restore that lost them. ([issue #16](https://github.com/Joaovitor404silva/NOLA-Stalker2-Coop/issues/16))
- **Items dropped by a joiner:** If the host loads an older save from before it picked up a joiner's drop, the drop comes back on the ground instead of being lost. Taking two stacked drops at once, or holding F to use one from the ground, now gives the right count. ([issue #16](https://github.com/Joaovitor404silva/NOLA-Stalker2-Coop/issues/16))

##### Loading and cutscenes
- **Host load freeze:** Loading a save on the host no longer hangs on a stuck loading step. The press-any-button screen after a load now closes by itself in about 30 seconds (it used to wait for a key, and joiners could be let into a frozen world).
- **Esc menu in cutscenes:** Opening the Esc menu during a cutscene no longer freezes the host's game time.

##### Enemies and mutants on a joiner's screen
- **Every nearby enemy is there:** A joiner now sees every enemy and mutant the host has near each player. Before, only the 8 nearest were sent: in a live check 7 of 15 bandits were missing, now none. ([issue #16](https://github.com/Joaovitor404silva/NOLA-Stalker2-Coop/issues/16))
- **Enemy health and death:** An enemy's health follows the host, and it dies right after the host's copy dies. Deaths now play the normal death instead of the burn animation. ([issue #16](https://github.com/Joaovitor404silva/NOLA-Stalker2-Coop/issues/16))
- **Bloodsuckers:** A bloodsucker that is cloaked for the host is cloaked for the joiner too, and visible when the host sees it. ([issue #16](https://github.com/Joaovitor404silva/NOLA-Stalker2-Coop/issues/16))
- **Enemy shots:** Joiners now see the bullets of enemies shooting, not only the muzzle flash.
- **Hits:** When a joiner shoots an enemy it flinches and bleeds like it does for the host.
- **Double enemies:** A real enemy and its copy no longer stand in the same place after a reload or a late stream-in.
- **No more rubber band:** Enemies that move on a joiner's screen are no longer pulled back to an old spot by the game.
- **Enemies around a far joiner:** When a joiner is far from the host, for example in a village, the enemies and NPCs around the joiner now appear for the joiner.
- **Leftover props:** Props left behind by a finished NPC action are removed on joiners.

##### Dead bodies
- **Missing corpses:** Bodies that were already lying near a player are now sent to every joiner. Before, some never showed up.
- **Corpses far away:** A body the game removed while a joiner was far away comes back when the joiner returns, in the same place and pose as the host's body.

##### Looks and animation
- **Floating weapons:** The weapon of a hidden NPC no longer floats in the air on a joiner's screen.
- **Enemy looks:** Vests, coats, mutant skins and other look parts now match the host's, and blood and damage marks on a body are copied.
- **Cover:** Enemies in cover keep the cover animation instead of standing up in the middle of it. Not perfect yet, see known issues.
- **Legs:** Walking and running enemies and dogs move their legs in step with the body more often. Fast running can still slide a little.

##### Story and missions
- **Host-only mission objects:** A joiner can no longer touch a mission object that the host's story runs (for example the scanner in the first mission). A short HUD text says why. The object's state (hidden, on, broken) is sent from the host to every joiner.
- **Trigger areas:** A joiner who stands inside a quest trigger area now counts for the host's quest, and the host stays inside while any joiner is in it.

#### Also in this build
These changes are in v1.3.0 but were not checked in a live session yet:
- Story quests are run only by the host. Joiners get their effects, dialogs and events from the host.
- Enemy copies on a joiner's screen are neutral to everything, so they no longer fight each other or the local townsfolk.
- A wounded enemy on the host also lies wounded on the joiner, and gets up when the host's one does.
- The bar cutscene in the first story part waits for the host's dialog before the joiner moves on.

### v1.2.1 (2026-10-28)

This update makes NOLA work on the new STALKER 2 game patch (Update 2.1, Steam build 26123434). With v1.2.0 on the new patch the co-op entries were missing from the main menu. Every player must install the same version, and v1.2.1 needs the new game patch.

#### Fixed
- **Game patch support:** every game address the mod uses was moved to the new patch, so all co-op features turn on again, including corpse sync and container loot sync.
- **UE4SS start crash ([issue #7](https://github.com/Joaovitor404silva/NOLA-Stalker2-Coop/issues/7)):** the two UE4SS signature files (`GUObjectArray.lua`, `ProcessLocalScriptFunction.lua`) were updated for the new patch. You no longer need to set `HookProcessLocalScriptFunction = 0`.
- **Quest sync:** the quest sync data was rebuilt from the new patch, so the quest steps the patch changed or added stay in sync between players.

### v1.2.0 (2026-10-25)

This update is about how your friends look and move in your game: the other players' characters now use far more of the game's own animations. It also fixes the problems reported in [issue #6](https://github.com/Joaovitor404silva/NOLA-Stalker2-Coop/issues/6). Every player must install the same version.

#### Fixed (issue #6)
- **Movement delay and fast catch-up:** when updates from the other player arrive late, their character keeps moving smoothly instead of freezing and then racing to catch up.
- **Invisible tutorial monster:** the monster after the bunker in the tutorial could hurt and kill a joiner without being visible to them. A joiner now only takes damage from enemies the host also has.
- **Partner gunshots:** you now hear the other player's gunshots and see the muzzle flash and the shot on their character.
- **Connection drops:** a joiner no longer hangs on the loading screen when the host loads. A joiner's game is saved when they leave, and their own worn gear is restored when they join again, so they don't come back holding items they never looted.
- **Death screen:** a co-op death shows the real cause (or the game's default text) instead of always "shot".

#### New
- **Friends on the compass:** each other player shows as a marker on your HUD compass at any distance, and it follows them as they move.

#### Your partner's character
- **Aiming and lowering the weapon:** rifles and pistols are held up in the aiming pose; pressing H lowers the weapon into the relaxed pose. In a safe zone the weapon is hidden, as it is for you.
- **Shooting:** each shot plays the game's own fire animation for that weapon, on the body and on the gun. The Mosin shows its bolt cycle.
- **Reloads:** rifles, shotguns, the SVD and the PKP play the body and weapon reload together, and the pistol stays in the hand while reloading.
- **Pistol, knife and bolt grips:** proper pistol grip, the game's knife grip (standing, walking, crouched) and a visible bolt in hand. With a detector out, the detector is in the left hand and the bolt in the right.
- **Movement:** lean left and right, crouch and stand-up transitions, smoother blends, vaulting over obstacles instead of through them, and ladder climbing with hands on the rungs.
- **Standing still:** feet stay planted. Before, the legs kept shifting as if the ground height was changing.
- **Stashes and bodies:** a partner who opens a stash crouches and searches for as long as it is open, then stands up when it closes. Searching a body plays the search animation.

#### Screenshots
Before and after shots of the partner fixes are in the [v1.2.0 folder](#nola-v1-2-0-readme).

#### Known limits
- No crouch-walk animation: the game has none for other characters, so a crouched partner slides along with still legs.
- Throwing the bolt uses the rifle grenade-throw motion.
- Not yet tested in a live session: a grenade throw seen on the partner.
- Movement smoothing over the Steam relay is in this build, but the remaining delay there was not measured (testing used LAN).
- Four and five player sessions are still lightly tested.

### v1.1 (2026-10-21)

#### Fixed
- **Ghost enemies:** some enemies (the tutorial bandits, the bandits attacking Zhorik in Zalissya) showed up only for joiners, standing still with no health. They are gone now: joiners see the same enemies as the host.
- **Stash window closing:** after one player emptied a stash (for example the mobile lab stash), the next player's window kept closing. It now opens, empty.
- **Shared stashes and boxes:** items a player puts into a stash or box now show up for everyone. Taking an item removes it for everyone, and only the player who took it gets it.
- **One player per box:** while a player is looking at or using a box, the others can't open it, the same as items on the ground.
- **Items keep everything:** items put into a box or dropped on the ground keep their condition, upgrades, attachments, loaded ammo and ammo type for the other players.
- **Dead bodies:** bodies no longer vanish from a joiner's screen when the host walks far away. They stay while any player is near them.
- **Quest sync:** quests no longer drift apart between host and joiner, and the joiner no longer reloads two or three times in a row to catch up.
- **Zhorik event and story characters:** characters that a quest spawns (Zhorik and his attackers in Zalissya, and others like them) now appear correctly for joiners, so these events play out for everyone.
- **Self-contained install:** every data table the mod needs is now inside the mod itself, so nothing depends on extra files in the bridge folder.

#### Known issues (planned for v1.2)
- Joiners see NPC animations reset now and then.
- On a joiner's screen, enemies that die sometimes play the anomaly death animation instead of the right one.
- The compass shows no direction marker for nearby enemies.
- Some enemy animations on a joiner's screen stutter or skip a frame.

### v1.0 (2026-10-21)
First release.

---

---

<a id="nola-roadmap"></a>

## Roadmap

### V1 (released: v1.0, now v1.2.1)
Host and join from the main menu, Steam or IP, up to 5 players, a shared world with host-run NPCs, shared drops, bodies, locks and quest items, a story that follows the host, your own character kept, downed and revive, friendly fire, loading together, three languages.

### Next (v1.3)
- NPC animations on joiners no longer reset.
- The right death animation for enemies on joiners (not the anomaly death).
- Enemy direction markers on the compass.
- Smooth enemy animations on joiners (no stutter or skipped frames).

### V2 (planned)
- The joiner is placed beside the host before the world loads, so there is no jump at all.
- A fix for the occasional extra body.
- A test of swapping host and joiner roles with a joiner's own save.
- A fix for NPC copy parking.
- Proper 3, 4 and 5 player live tests.
- Keep weapon upgrades on restored items.
- Shared trader stock.

### Ideas (studied, not promised)
- Voice chat on one key (close range and radio).
- Harder enemies when more players are in the Zone.
- Shared map waypoint and teammate markers on the PDA map.
- A settings page in the game and a connection indicator.
- Travelling together and regrouping.
- Companions that take orders.
- Moving the A-Life around when players are far apart.

</details>

<details>
<summary>Original project overview and credits</summary>

<p align="center"><img src="assets/nola_title.png" alt="NOLA - No One Left Alone" width="720"></p>

<p align="center"><b>Co-op for S.T.A.L.K.E.R. 2: Heart of Chornobyl. Walk the Zone with friends, in the same world, each with your own character.</b></p>

<p align="center">
<a href="https://www.nexusmods.com/stalker2heartofchornobyl/mods/3050">Nexus Mods</a> ·
<a href="https://github.com/Joaovitor404silva/NOLA-Stalker2-Coop/releases/latest">Download</a> ·
<a href="#nola-changelog">Changelog</a> ·
<a href="https://ko-fi.com/jaumn">Support on Ko-fi</a>
</p>

<p align="center"><a href="https://ko-fi.com/jaumn"><img src="https://ko-fi.com/img/githubbutton_sm.svg" alt="Support NOLA on Ko-fi"></a></p>

> Status: **v1.3.2** (see the [Changelog](#nola-changelog)). It works and has been played a lot in testing, but it is not finished and it will have bugs. Please read [Known issues](#nola-known-issues) before you start.

---

## What NOLA is

NOLA is a fan-made co-op mod for S.T.A.L.K.E.R. 2: Heart of Chornobyl. One player hosts and runs the Zone. Up to five players (the host plus four friends) share that world: you see each other, fight the same enemies, loot the same bodies, follow the same story, and pick each other up when you go down.

The host's world is the real one: the host decides what the A-Life, the NPCs, the weather and the quests do. Everyone else joins that world and keeps their own character (gear, condition, attachments and health). If you do not press the co-op buttons, the game plays like normal solo STALKER 2.

NOLA is free and open source under the [GPL-3.0 licence](LICENSE).

## At a glance

- Up to **5 players**: the host plus four friends.
- Connect through **Steam friends** or **LAN / IP** (VPN works too).
- One shared Zone: same NPCs, enemies, loot and story, run by the host.
- Every player keeps their **own character**.
- Downed and revive, friendly fire, and everyone loads together with the host.
- Solo play is unchanged when you don't press the co-op buttons.

## Play

Download the latest release from [Nexus Mods](https://www.nexusmods.com/stalker2heartofchornobyl/mods/3050) or [GitHub Releases](https://github.com/Joaovitor404silva/NOLA-Stalker2-Coop/releases/latest), then follow [Install and play](#nola-install).

| Page | What is in it |
|---|---|
| [Features](#nola-features) | Every feature, grouped by area, with how well it is tested |
| [Known issues](#nola-known-issues) | What is broken or not checked yet |
| [Changelog](#nola-changelog) | What changed in each version |
| [Roadmap](#nola-roadmap) | What is released, what is next, what is planned for V2, and ideas |
| [Install and play](#nola-install) | Requirements and a quick start |
| [Settings](#nola-flags) | What each setting does and how to turn features off |
| [FAQ](#nola-faq) | Common questions |
| [Credits](#nola-credits) | Credits, disclaimer and AI disclosure |

## Source code

This repository holds the full source of the mod: the native UE4SS C++ mod, the data tables, the offline tests, the packaging and installer scripts, and the reverse-engineering scripts.

| Folder | What is in it |
|---|---|
| `src/` | The native mod (`main.dll`), C++ on top of [RE-UE4SS](https://github.com/UE4SS-RE/RE-UE4SS) |
| `cppbuild/` | CMake build of the DLL |
| `data/` | Tables the DLL embeds (IDs and rules, no game text) |
| `tools/` | Generators for the data tables, build and test helpers |
| `tests/` | Offline tests, run by CI on every pull request |
| `assets/` | NOLA's own art (title logo) |
| `modwork/` | Pak build, release builder, installer, Lua side, dev tools |
| `re/` | Ghidra scripts and the name database builder (you generate the data from your own game) |
| `docs/` | Design notes |

Building, testing and the folder setup are in [DEVELOPING.md](#nola-developing).

## How to contribute

NOLA is made by one person, so every bit of help counts. You don't need to know how to code to help!

### 🐞 Report a bug
[Open an issue](https://github.com/Joaovitor404silva/NOLA-Stalker2-Coop/issues/new) and start the title with **[Bug]**. Please include:

- **What happened**, and what you expected to happen.
- **How to make it happen again**, step by step if you can.
- **Who was hosting**, how many players were in, and whether you used **Steam** or **LAN / IP**.
- Your **NOLA version** (for example v1.3.2) and your **game build** (Steam → right-click the game → Properties → Updates).
- The **UE4SS.log** from **every player**. It's in `Stalker2\Binaries\Win64\ue4ss\` inside the game folder. Drag the file into the issue.
- A **screenshot or short video** if it's something you can see.

Check [Known issues](#nola-known-issues) first. Your bug might already be on the list.

### 💡 Suggest an idea
[Open an issue](https://github.com/Joaovitor404silva/NOLA-Stalker2-Coop/issues/new) with **[Idea]** in the title: what you'd like, why it would make co-op more fun, and which other game does it well. Have a look at the [Roadmap](#nola-roadmap) first.

### 🧪 Help with testing
Most wanted: **4 and 5 player** sessions, **long sessions**, **missions further into the story**, and **other mods** next to NOLA. Tell us how it went in an issue with **[Test]** in the title, even if everything worked.

### 🌍 Translations
NOLA's texts are in English, Portuguese and Spanish. They live in `data/nola_texts.tsv`. Open an issue or a pull request with **[Translation]** in the title.

### 🛠️ Code
Fixes and features are welcome as pull requests. Read [CONTRIBUTING.md](#nola-contributing) first: it has the rules, the PR checklist and how CI checks your change.

### ☕ Tip the developer
NOLA is free and always will be. If you enjoy it and want to say thanks, you can leave a tip on [Ko-fi](https://ko-fi.com/jaumn). It is never required.

## Rules

- Be kind and patient, in issues, pull requests and anywhere else. No harassment, insults or hate.
- **No game files.** Never post or commit files from the game: paks, assets, `.cfg` dumps, the exe, decompiled game code or saves.
- **No piracy.** NOLA is for people who own the game. Issues about cracked copies are closed.
- **No cheats in public games and no paid features.** NOLA is a free co-op mod.
- **No personal data.** Remove your IP, Steam ID and real name from logs before you post them.

## Disclaimer

- S.T.A.L.K.E.R. 2: Heart of Chornobyl is the work of GSC Game World. NOLA is an unofficial, non-commercial fan project. It is not affiliated with, endorsed by or supported by GSC Game World or its publishers. All game names, art and trademarks belong to their owners.
- This repository does not contain or redistribute the game, its files or its code. You need your own legal copy of the game.
- NOLA is provided as it is, with no warranty. Use it at your own risk, and back up your saves.
- **AI disclosure:** NOLA was developed with heavy help from AI coding assistants (Claude, by Anthropic) under the author's direction, including code, tests and documentation. The author set the goals, ran the game tests and decided what shipped.

## Licence

Copyright (C) 2026 Jaumn and NOLA contributors.

NOLA is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, version 3 or (at your option) any later version. See [LICENSE](LICENSE).

Third-party parts keep their own licences: [RE-UE4SS](https://github.com/UE4SS-RE/RE-UE4SS) (MIT, including `modwork/s2coop/Mods/shared/UEHelpers`) and [PolyHook 2](https://github.com/stevemk14ebr/PolyHook_2_0) (MIT, pulled in by RE-UE4SS). Neither is copied into this repository except `UEHelpers`.

[![made with universal-modder](https://raw.githubusercontent.com/rehan-remade/universal-modder/main/docs/media/made-with-dark.svg)](https://github.com/rehan-remade/universal-modder)

<a id="nola-credits"></a>

## Credits

**Custom stability 0.5 changes:** prepared for dreadnaughtgaming with assistance from OpenAI Codex. Original NOLA authorship remains with Jaumn and the contributors listed below. This is an unofficial modified build.

- **Jaumn**: creator of NOLA. Design, programming, testing and many nights in the Zone. NOLA started with one simple wish: to walk the Zone with friends instead of alone.
- **The UE4SS team**: the mod loader that lets mods like this run inside Unreal Engine games. NOLA would not exist without it. UE4SS (UE4SS-RE project) is released under the MIT licence, and the licence file is shipped with NOLA.
- **GSC Game World**: for creating the Zone, keeping the spirit of the series alive, and the official modding tools that help the community understand the game.
- **Sternab**: the fix for identical items vanishing next to a picked-up item (v1.3.1).
- **Testers and friends**: thanks to everyone who jumped into broken builds and reported every bug. Every fix exists because someone tested it first.
- **The STALKER community**: to every modder who shared knowledge and every player who ever asked "can we play this together?". This one is for you.
- S.T.A.L.K.E.R. 2: Heart of Chornobyl is the work of GSC Game World. NOLA is an unofficial, non-commercial fan project. It is not affiliated with, endorsed by or supported by GSC Game World or its publishers. All game names, art and trademarks belong to their owners. NOLA does not contain or redistribute the game, and you need your own copy.
- NOLA is a free hobby and study project. It is provided as it is, with no warranty. Use it at your own risk.
- **AI disclosure:** NOLA was developed with heavy help from AI coding assistants (Claude, by Anthropic) under the author's direction, including code, tests and documentation. The author set the goals, ran the game tests and decided what shipped.

</details>

<details>
<summary>Contributing, development and technical reference</summary>

<a id="nola-contributing"></a>

## Contributing

Thanks for helping! Bug reports, test reports, translations, docs and code are all welcome. For reports and ideas, see [How to contribute](#how-to-contribute). This page is about pull requests.

### The hard rules

A pull request that breaks one of these is closed. CI checks the first two.

1. **No game files.** Never commit anything from the game or extracted from it: `.pak`, `.utoc`, `.ucas`, `.uasset`, `.uexp`, the exe or its DLLs, `.cfg` dumps from the game's paks, game text, audio, textures or models.
2. **No binaries and no saves.** No `.dll`, `.exe`, `.lib`, `.sav`, `.zip` or `.7z`. Releases are built from source.
3. **No decompiled game code.** You may read your own decompile to understand the game. Write the mod's code yourself; never paste decompiler output, and don't commit the decompile or the name database you build from it.
4. **No third-party code without its licence.** Code you copy must have a GPL-3.0 compatible licence, and you keep its notice.
5. **No personal data.** No IPs, Steam IDs, user names or paths with your name in code, tests or logs.
6. **No cheats for other people's games, no paywalls, no telemetry.**

By opening a pull request you agree that your change is released under the [GPL-3.0 licence](LICENSE).

### How a change gets in

1. Fork the repo and branch from `main`.
2. One fix or feature per pull request. Keep it small.
3. Add or update an offline test in `tests/` that fails before your change and passes after it.
4. Run the tests (see [DEVELOPING.md](#nola-developing)).
5. If you changed a table generator, regenerate the table in `data/` and commit both.
6. If players will notice the change, say so in the PR so it can go into the [Changelog](#nola-changelog).
7. Open the pull request and fill in the template.

`main` is protected: every change goes through a pull request, CI must pass, and the maintainer reviews and merges it. Nobody pushes to `main` directly.

### What CI checks

The `ci` workflow runs on every pull request:

- **Repo rules**: no game files, binaries, saves, or files over 5 MB.
- **Offline tests**: `tools\run_tests.ps1 --all` builds the C++ test programs with MSVC and runs every suite against `tests/baseline.tsv`. Suites that need the game, a save or a local decompile are reported as `SKIP`; that is fine.

Live tests in the real game are run by the maintainer before a release. If your change affects what players see or do, describe how you tested it in game (two PCs, or two game copies on one PC) and add screenshots if you can.

### Style

- C++ in `src/` follows the code around it: short names, one module per `s2*_` prefix.
- No commented-out code.
- Python tools run with `uv run --no-project python -I`.
- Text files keep their current line endings (the repo stores them as they are).

---

<a id="nola-developing"></a>

## Development

### Requirements

- Windows 10/11 x64 and your own copy of S.T.A.L.K.E.R. 2 on Steam (game build 26123434 for v1.3.x).
- Visual Studio 2022 Build Tools (MSVC, CMake, Ninja) and Rust stable (MSVC toolchain), both needed by RE-UE4SS.
- A [RE-UE4SS](https://github.com/UE4SS-RE/RE-UE4SS) checkout (tested at `5e62799`).
- [uv](https://docs.astral.sh/uv/) for the Python tools and tests, Node.js 20+ for the RE helper scripts.

### Folder setup

Several scripts still use the original dev machine's absolute paths. The easiest fix is to create these junctions (run in an admin `cmd`), or change the paths in the scripts:

| Expected path | Point it at |
|---|---|
| `D:\modding\cpp\S2CoopPort` | this checkout |
| `D:\modding\cpp\RE-UE4SS` | your RE-UE4SS checkout (used by `cppbuild/CMakeLists.txt`) |
| `<game>\ModWork` | `modwork\` in this checkout |

```
mklink /J D:\modding\cpp\S2CoopPort <this checkout>
mklink /J D:\modding\cpp\RE-UE4SS <your RE-UE4SS checkout>
mklink /J "<game>\ModWork" <this checkout>\modwork
```

Pull requests that replace a hard-coded path with a relative one are welcome.

### Build the DLL

```
cppbuild\build.bat
```

The output is `cppbuild\Output\...\Game__Shipping__Win64\` (`main.dll`). `tools\nola_build_fast.bat` and `tools\nola_build_cached.bat` do incremental builds, and `tools\build_rel.ps1` makes a release build.

The DLL embeds the tables in `data/`. If you change a generator's input, regenerate its table first: `uv run --no-project python -I tools\gen_<table>.py`. How runtime tables work is in [docs/RELEASE.md](#nola-docs-release).

### Run the tests

```
powershell -File tools\run_tests.ps1 --all --jobs 4
```

The runner reads `tests/suites.tsv` (one row per suite: steps, needed files, the source globs that trigger it) and compares the result with `tests/baseline.tsv`. A suite whose `needs` files are missing prints `SKIP`. CI runs the same command on every pull request.

Some suites need things you make yourself and never commit: a save from your own game, the game exe, a local decompile, or the quest node sources unpacked from your game's paks. They `SKIP` until you have them.

### Paks and the release package

- `modwork\s2coop\tools\build_paks.py` builds the `zzzzzz_*` override paks from `modwork\s2coop\paksrc\`. That folder holds files that start as copies of the game's own `.cfg` files, so it is **not** in this repository. Unpack the files you need from your own game, and only commit the scripts.
- `modwork\s2coop\tools\build_release_cpp.py` assembles the release payload (UE4SS, the DLL, the paks and `flags.txt`) and the installer in `modwork\s2coop\tools\installer\`.

### Install a dev build

Copy the payload into `Stalker2\Binaries\Win64\` and the pak into `Stalker2\Content\Paks\~mods\`, like the [manual install](#nola-install). `tools\hotreload.ps1` swaps a new DLL into a running game.

For live debugging, [Game Crawler](https://github.com/Joaovitor404silva/Game-Crawler) (an in-process debugger with an MCP server) and its [Anomaly Scanner](https://github.com/Joaovitor404silva/Anomaly-Scanner) plugin work with NOLA.

### Reverse engineering

The repo has no decompile and no game symbols. Build them from your own copy of the game:

1. Copy `Stalker2\Binaries\Win64\Stalker2-Win64-Shipping.exe` somewhere else. Never work on the Steam file.
2. Import it into Ghidra 12.1.x (JDK 21, about 32 GB RAM) headless, with `re\ghidra_scripts\FastOpts.java` as a pre-script. Analysis takes hours.
3. Apply engine types from a live reflection dump with `ApplySdk.java`.
4. `node re\s2names\build_names.js` builds your local `names.tsv`; `re\ghidra_scripts\apply_names.ps1` applies it. Keep `names.tsv` local.
5. `DecompDump.java` dumps the decompile, and `node re\s2decomp\build_index.js` indexes it. Keep it local.

Use what you learn to write your own code. Don't commit decompiler output (see [CONTRIBUTING.md](#nola-contributing)).

### Design notes

- [docs/RELEASE.md](#nola-docs-release): what a release contains and how runtime tables are embedded.
- [docs/STEAM_DESIGN.md](#nola-docs-steam-design): how the Steam connection works.

<a id="nola-data-readme-d1"></a>

## D1 data reference

Generated by `convert_d1.py` (run: `uv run --no-project --with lupa python -I convert_d1.py`). Do not edit the TSV files by hand.

### Format (long form, one row per leaf value)
- Line 1 is the header. Tab separated, UTF-8, LF line endings, no comments, no BOM.
- Columns: `k1` .. `kD` (key path, D = depth of that file, see the table below), `t` (value type), `v` (value).
- A key cell is the key with a type letter: `s` + text for a string key, `i` + digits for an integer key. Unused key cells are empty.
  Key cells fill from `k1` to the left; an empty cell ends the path.
- `t`: `s` string, `i` integer, `f` float (Lua float, shown with a dot or exponent), `b` boolean (`true`/`false`), `e` empty table (`v` empty).
- `v`: the value. Escapes: `\\` = backslash, `\t` = tab, `\r` = CR, `\n` = LF. Other text is raw.
- Lua arrays are integer keys 1..n in the `i` form. Rows are sorted by key path.
- Loader rule: split each line on tab, rebuild the path from the key cells, and set the leaf. Duplicate paths are an error.

### Files

| TSV | Source (ModWork) | Lines | Rows | Depth | Round trip | Notes |
|---|---|---|---|---|---|---|
| s2u_actions.tsv | release\S2Coop\bridge\s2u_actions.lua (md5 85cd25d0) | 1-325 (whole file) | 7524 | 4 | OK | - |
| s2u_anomaly.tsv | release\S2Coop\bridge\s2u_anomaly.lua (md5 8626fb18) | 1-18 (whole file) | 52 | 2 | OK | - |
| s2u_choice.tsv | release\S2Coop\bridge\s2u_choice.lua (md5 195ebf8a) | 1-2214 (whole file) | 7337 | 3 | OK | - |
| s2u_cine.tsv | release\S2Coop\bridge\s2u_cine.lua (md5 b4186953) | 1-261 (whole file) | 768 | 3 | OK | - |
| s2u_destruct.tsv | release\S2Coop\bridge\s2u_destruct.lua (md5 e136de24) | 1-396 (whole file) | 3128 | 2 | OK | - |
| s2u_dlg_header.tsv | release\S2Coop\bridge\s2u_dlg.lua (md5 1def2d09) | 1-8176 (whole file) | 22 | 2 | OK | dropped set (8164 rows) |
| s2u_qdrop.tsv | release\S2Coop\bridge\s2u_qdrop.lua (md5 c84198de) | 1-328 (whole file) | 323 | 2 | OK | - |
| s2u_qitems.tsv | release\S2Coop\bridge\s2u_qitems.lua (md5 7cf083bd) | 1-1222 (whole file) | 2109 | 3 | OK | - |
| s2u_qpick.tsv | release\S2Coop\bridge\s2u_qpick.lua (md5 9b3cff04) | 1-1903 (whole file) | 3556 | 3 | OK | - |
| s2u_vendor.tsv | release\S2Coop\bridge\s2u_vendor.lua (md5 5f99a5f2) | 1-226 (whole file) | 606 | 3 | OK | - |
| flags_s2core.tsv | s2coop\Mods\S2CoopAlife\Scripts\s2core.lua (md5 0b56e1b5) | 12-433 | 546 | 1 | OK | duplicate top-level keys in source: emgrace |
| flags_main.tsv | s2coop\Mods\S2CoopAlife\Scripts\main.lua (md5 76717baf) | 2278-2278 | 55 | 1 | OK | - |
| weapons_main.tsv | s2coop\Mods\S2CoopAlife\Scripts\main.lua (md5 76717baf) | 734-773 | 190 | 2 | OK | - |
| diff_weapon_mult_main.tsv | s2coop\Mods\S2CoopAlife\Scripts\main.lua (md5 76717baf) | 776-776 | 4 | 1 | OK | - |

### Top-level keys per file (first key column)

- `s2u_actions.tsv`: BP_100_Rads_Bar_120_C, BP_100_Rads_Bar_80_C, BP_Arena_120_C, BP_Arena_80_C, BP_Arena_Closet_C, BP_AzimutRepeater_C, BP_Bandits_80_C, BP_Board_C, BP_BunkerDoor_01_C, BP_BunkerDoor_02_C, BP_BunkerDoor_03_C, BP_BunkerDoor_04_C, BP_BunkerDoor_05_C, BP_BunkerDoor_06_C, BP_BunkerDoor_07_C, BP_BunkerHatch_Electric_C, BP_BunkerHatch_Valve_C, BP_Button_Elevator_C, BP_Button_Elevator_x16_C, BP_Button_Horizontal_C, BP_Button_Invisible_C, BP_Button_Vertical_C, BP_Button_Vertical_E16_C, BP_Cardlock_C, BP_Cardlock_E11_MQ01_C, BP_CartridgePanel_Deinstall_C, BP_CartridgePanel_Install_C, BP_Chemical_Plant_120_C, BP_CodeLock_C, BP_CompactPsyEmmiter_C, BP_CompactPsyEmmiter_SQ06_C, BP_Concrete_Plant_120_C, BP_Concrete_Plant_80_C, BP_CutsceneInteractWithDeactivate_C, BP_CutsceneInteract_C, BP_Dalins_Lamp_C, BP_Dalins_Photo_C, BP_Dalins_Safe_C, BP_DecalFakeRectLight_C, BP_DecalFakeSpotLight_C, BP_DestructibleTransformator_C, BP_Diesel_Generator_Base_C, BP_Diesel_Generator_New_C, BP_Diesel_Generator_New_Int_C, BP_Diesel_Generator_Old_C, BP_Diesel_Generator_Old_Int_C, BP_Duty_120_C, BP_Duty_80_C, BP_DynamicObject_2states_final_C, BP_DynamicObject_Decal_C, BP_DynamicObject_Sound_C, BP_DynamicObject_VFX_C, BP_E01_MQ01_Barge_80_C, BP_E15_Bunker_Switch_C, BP_EQ32_Military_Radio_C, BP_Elevator_Industrial_C, BP_Elevator_LivingHouse_Large_C, BP_Elevator_LivingHouse_Small_C, BP_Elevator_LivingHouse_Small_Fake_C, BP_Elevator_SIRCAA_C, BP_Elevator_SIRCAA_X11_C, BP_EmitterPart_Deinstall_C, BP_EmitterPart_Install_C, BP_EnergyPillar_C, BP_ExplosivesPackage_C, BP_FogToxic_Dynamic_E06_MQ01_C, BP_Freedom_120_C, BP_Freedom_80_C, BP_FusePanel_C, BP_Horror_Radio_C, BP_Icarus_120_C, BP_Icarus_80_C, BP_IllusoryObstaclePlaceholder_C, BP_Inductor_E06_MQ01_C, BP_Infostand_C, BP_Interactable_Note_Base_C, BP_Interactable_Note_C, BP_Interactable_PDA_C, BP_Interactable_Radio_120_C, BP_Interactable_Radio_80_C, BP_Interactable_USB_C, BP_Jammer_C, BP_Kazkovy_Hub_120_C, BP_Kazkovy_Hub_80_C, BP_L_WallMount_C, BP_L_cit_StreetLantern_C, BP_L_cit_lamp_interior_01_d_01_C, BP_L_cit_lamp_interior_01_e_01_C, BP_L_cit_lamp_interior_01_e_02_C, BP_L_cit_lamp_interior_01_g_final_C, BP_L_cit_lamps_01_h_final_C, BP_L_cit_light_interior_02_a_C, BP_L_cit_light_interior_02_b_C, BP_L_ele_FloorLamp_C, BP_L_ele_LEDLamp_C, BP_L_ele_LampInterior_C, BP_L_ele_LampShade_C, BP_L_ele_LepLamp_C, BP_L_ele_SpotlightLeg_C, BP_L_ele_StreetLamp_01_C, BP_L_ele_TableLamp_C, BP_L_ele_WallLamp_C, BP_L_ele_ceiling_lamp_02_final_C, BP_L_ele_ceiling_lamp_07_a_01_C, BP_L_ele_ceiling_lamp_07_b_C, BP_L_ele_heater_01_b_C, BP_L_ele_heater_01_c_C, BP_L_ele_lamp_02_a_C, BP_L_ele_lamp_03_final_C, BP_L_ele_lamp_04_a_C, BP_L_ele_lamp_05_a_C, BP_L_ele_lamp_08_a_C, BP_L_ele_lamp_08_b_C, BP_L_ele_monitor_03_d_C, BP_L_ele_old_pc_02_C, BP_L_ele_spotlight_01_a_01_C, BP_L_ele_spotlight_01_b_01_C, BP_L_ele_spotlight_01_bulbs_a_C, BP_L_ele_wall_lamp_01_a_C, BP_L_ele_wall_lamp_02_final_C, BP_L_ele_wall_lamp_04_C, BP_L_flashlight_01_C, BP_L_gen_alarm_lamp_01_a_C, BP_L_gen_candles_01_a_01_C, BP_L_gen_candles_01_b_01_C, BP_L_gen_candles_01_c_01_C, BP_L_gen_candles_01_d_01_C, BP_L_gen_candles_01_e_01_C, BP_L_gen_candles_01_f_01_C, BP_L_gen_candles_01_g_C, BP_L_gen_candles_01_h_C, BP_L_gen_candles_01_k_C, BP_L_gen_candles_01_l_C, BP_L_gen_candles_01_m_C, BP_L_gen_candles_01_n_C, BP_L_gen_candles_01_o_C, BP_L_gen_candles_01_p_C, BP_L_gen_kerosene_lamp_01_01_C, BP_L_gen_kerosene_lamp_02_01_C, BP_L_gen_lamp_illich_01_a_C, BP_L_gen_lamp_illich_01_a_blue_C, BP_L_gen_lamp_illich_01_a_green_C, BP_L_gen_lamp_illich_01_a_red_C, BP_L_gen_lamp_illich_01_cable_C, BP_L_gen_pillar_lamp_01_a_01_C, BP_L_gen_pillar_lamp_01_b_01_C, BP_L_ind_lamp_02_C, BP_L_ind_lamp_03_C, BP_L_ind_lamp_06_C, BP_L_lab_computers_01_d_C, BP_L_mod_ceiling_lamp_01_C, BP_L_roc_stalactite_03_a_C, BP_L_roc_stalactite_03_b_C, BP_L_roc_stalactite_03_c_C, BP_L_roc_stalactite_03_d_C, BP_L_roc_stalactite_03_e_C, BP_L_uni_bun_ceiling_lamp_01_a_C, BP_L_uni_nii_emitter_09_new_C, BP_L_uni_nii_emitter_12_new_C, BP_L_uni_nii_emitter_14_a_C, BP_L_uni_nii_pole_01_C, BP_L_uni_nii_pole_02_C, BP_L_uni_nii_pole_03_C, BP_L_vil_kerosene_lamp_01_01_C, BP_L_vil_lep_lamp_01_C, BP_Laptop_C, BP_Latch_Cit_C, BP_Latch_Vil_C, BP_Lever_Big_Horizontal_C, BP_Lever_Horizontal_C, BP_Lever_Vertical_C, BP_Light_Base_C, BP_Light_Destr_GlassMonitor_01_00_C, BP_Light_Destr_GlassMonitor_02_00_C, BP_Light_Destr_GlassMonitor_03_00_C, BP_Light_Destr_GlassMonitor_04_00_C, BP_Light_Destr_GlassMonitor_05_00_C, BP_Light_Destr_GlassMonitor_06_00_C, BP_Light_Destr_GlassMonitor_07_00_C, BP_Light_Destr_PromLamp_01_00_C, BP_Light_Destr_PromLamp_04_00_C, BP_Light_Destr_PromLamp_06_00_C, BP_Light_Destr_PromLamp_09_00_C, BP_Light_Destr_PromLamp_10_00_C, BP_Light_Indestr_PromLamp_01_00_C, BP_Light_Indestr_PromLamp_02_00_C, BP_Light_Indestr_PromLamp_03_00_C, BP_Light_Param_C, BP_Light_SwichDestr_KerosineLamp_02_00_C, BP_Local_Fog_Interactive_C, BP_MQ11_SteamFloor_C, BP_Mercenaries_120_C, BP_Mercenaries_80_C, BP_Militaries_120_C, BP_Militaries_80_C, BP_Military_Radio_C, BP_Military_Radio_E05_MQ01_C, BP_Mix_120_C, BP_Mix_80_C, BP_MonitorSection_C, BP_MonitorSection_Small_C, BP_Neutrals_120_C, BP_Neutrals_80_C, BP_OpeningContainer_C, BP_Osciloscope_RadioSilence_C, BP_Padlock_Prototype_01_C, BP_Padlock_Prototype_02_C, BP_PlayerStash_C, BP_PseudoBrainPostProcess_C, BP_PsyBeacon_C, BP_PsyLocator_C, BP_PsyLocator_SQ92_C, BP_Quiets_Room_120_C, BP_Quiets_Room_80_C, BP_ReceiverAND_C, BP_STC_Malachite_120_C, BP_STC_Malachite_80_C, BP_Safe_Big_C, BP_Safe_Big_Small_C, BP_ScanningLocator_C, BP_Shevchenko_120_C, BP_Shevchenko_80_C, BP_ShroudOfDarkness_C, BP_Sidorovichs_Bunker_120_C, BP_Sidorovichs_Bunker_80_C, BP_SignatureReader_C, BP_Skadovsk_120_C, BP_Skadovsk_80_C, BP_SkifsFinal_Container_C, BP_SkifsFinal_OKTA_C, BP_SkifsFinal_Switch_C, BP_Slag_Heap_120_C, BP_Slag_Heap_80_C, BP_Speaker_C, BP_StunVolume_C, BP_Teleport_Instant_C, BP_Teleport_Portal_Bubble_C, BP_Teleport_Portal_C, BP_TopazScanner_Broken_C, BP_TopazScanner_Overworld_C, BP_TopazScanner_Prologue_C, BP_Topaz_Fake_C, BP_Trap_Shotgun_C, BP_TriggerSignal_C, BP_Turnstile_C, BP_Valve_Base_C, BP_Valve_Big_Horizontal_C, BP_Valve_Big_Vertical_C, BP_Valve_Small_Horizontal_C, BP_Valve_Small_Vertical_C, BP_VentBlades_Horizontal_C, BP_VentBlades_WithoutSound_C, BP_VentBlades_new_C, BP_Visiograph_ControlPanel_C, BP_Visiograph_Face_C, BP_Walkie_Talkie_C, BP_Wire_C, BP_WishGranter_Monolit_C, BP_WishGranter_Skif_C, BP_WishGranter_Strelok_C, BP_Yaniv_Station_120_C, BP_Yaniv_Station_80_C, BP_ZAZ_C, BP_ZAZ_Handle_C, BP_ZAZ_Hood_C, BP_ZAZ_Roof_C, BP_ZAZ_Wheel_C, BP_Zalissya_Bar_120_C, BP_Zalissya_Bar_80_C, BP_cit_lamp_interior_01_d_C, BP_cit_lamp_interior_01_e_C, BP_cit_lamp_interior_01_g_C, BP_cit_lamp_interior_01_h_C, BP_cit_lamps_01_h_C, BP_cit_refregerator_1_C, BP_cit_refregerator_2_C, BP_cit_room_props_tableLamp_1_C, BP_ele_ceiling_lamp_02_C, BP_ele_lamp_02_C, BP_ele_lamp_03_C, BP_ele_lamp_04a_C, BP_ele_lamp_05_C, BP_ele_monitor_02_C, BP_ele_monitor_03_c_C, BP_ele_spotlight_01_a_C, BP_ele_table_lamp_01_C, BP_ele_wall_lamp_01_C, BP_ele_wall_lamp_02_C, BP_fur_cit_closet_2_C, BP_fur_cit_closet_3_C, BP_fur_hospital_cabinet_1_C, BP_fur_kinder_cabinet_1_C, BP_fur_kinder_cabinet_3_C, BP_fur_liv_wal_closet_1_C, BP_fur_liv_wal_closet_2_C, BP_fur_med_cupboard_1_C, BP_fur_med_cupboard_2_C, BP_fur_old_cupboard_1_C, BP_fur_old_cupboard_2_C, BP_fur_sport_cabinet_1_C, BP_fur_sport_cabinet_2_C, BP_fur_sport_cabinet_3_C, BP_fur_vil_chest_1_C, BP_fur_vil_chest_2_C, BP_fur_vil_chest_3_C, BP_gar_box_1_C, BP_gen_candles_01_a_C, BP_gen_candles_01_b_C, BP_gen_candles_01_c_C, BP_gen_candles_01_d_C, BP_gen_candles_01_e_C, BP_gen_candles_01_f_C, BP_gen_kerosene_lamp_C, BP_gen_wooden_boxes_01_a_cap_C, BP_int_fur_locker_02_door_01_C, BP_int_gun_cabinet_door_01_C, BP_mod_stairs_01_C, BP_test_sender_C, BP_vil_kerosene_lamp_01_C, INVALID_BP_Folded_Ladder_C
- `s2u_anomaly.tsv`: BP_CarouselAnomaly_C, BP_ChemicalAnomaly_C, BP_ClassicFireAnomaly_C, BP_ElectroAnomaly_C, BP_ElectroAnomaly_Dynamic_C, BP_ExpulsionAnomaly_C, BP_FlycatcherAnomaly_C, BP_LavaLampAnomaly_C, BP_PillowAnomaly_C, BP_RazorAnomaly_C, BP_SoapBubbleAnomaly_C, BP_SpringboardAnomaly_C, BP_SteamAnomaly_C
- `s2u_choice.tsv`: V, item, npc, stats, trig, use
- `s2u_cine.tsv`: lead, scene
- `s2u_destruct.tsv`: SM_Lab_dishes_1_10, SM_Lab_dishes_1_11, SM_Lab_dishes_1_12, SM_Lab_dishes_1_13, SM_Lab_dishes_1_14, SM_Lab_dishes_1_15, SM_Lab_dishes_1_16, SM_Lab_dishes_1_17, SM_Lab_dishes_1_18, SM_Lab_dishes_1_19, SM_Lab_dishes_1_2, SM_Lab_dishes_1_20, SM_Lab_dishes_1_21, SM_Lab_dishes_1_22, SM_Lab_dishes_1_23, SM_Lab_dishes_1_24, SM_Lab_dishes_1_3, SM_Lab_dishes_1_4, SM_Lab_dishes_1_5_1, SM_Lab_dishes_1_5_2, SM_Lab_dishes_1_7, SM_Lab_dishes_1_8, SM_Lab_dishes_1_9, SM_air_mi24_wheelB_01, SM_air_mi_6_wheel_front_02, SM_air_mi_6_wheel_rear_03, SM_cit_canister_02_a, SM_cit_canister_02_b, SM_cit_chairs_01_a, SM_cit_chairs_01_b, SM_cit_chairs_01_c, SM_cit_chairs_01_d, SM_cit_flower_pot_02_a, SM_cit_flower_pot_02_b, SM_cit_flower_pot_02_c, SM_cit_flower_pot_02_d, SM_cit_flower_pot_02_e, SM_cit_flower_pot_02_f, SM_cit_houseware_01_b, SM_cit_houseware_01_d, SM_cit_houseware_01_f, SM_cit_lamp_interior_01, SM_cit_plastic_barrel_01, SM_cit_stroller_01_a, SM_cit_stroller_01_b, SM_cit_weghing_machine_01, SM_cit_window_glass_01, SM_cit_window_glass_01_a, SM_cit_window_glass_01_b, SM_cit_window_glass_01_c, SM_cit_window_glass_01_d, SM_cns_beer_a, SM_cns_canned_meat_01_c, SM_cns_cossacks_vodka_01_a, SM_cns_water_a, SM_dch_ske_01_a, SM_dch_ske_01_b, SM_dis_beer_glass_01, SM_dis_boiling_pan_01, SM_dis_coffee_maker_01_a, SM_dis_coffee_maker_01_b, SM_dis_cup_holder_01_a, SM_dis_cup_holder_01_b, SM_dis_faceted_glass_01_a, SM_dis_kitchen_item_02_01, SM_dis_kitchen_item_02_02, SM_dis_kitchen_item_02_03, SM_dis_kitchen_item_02_04, SM_dis_kitchen_item_02_15, SM_dis_kitchen_item_02_16, SM_dis_kitchen_item_02_17, SM_dis_metal_cup_01, SM_dis_metal_lplate_01, SM_dis_pan_01_a, SM_dis_pan_01_b, SM_dis_pan_02_a, SM_dis_pan_02_b, SM_dis_pan_02_c, SM_dis_pan_02_d, SM_dis_pan_02_e, SM_dis_pan_02_f, SM_dis_pan_02_g, SM_dis_pan_02_h, SM_dis_pan_02_o, SM_dis_pan_02_p, SM_dis_pan_02_q, SM_dis_pan_02_r, SM_dis_pan_02_s, SM_dis_pan_02_t, SM_dis_vodka_glass_01_a, SM_ele_ceiling_lamp_01, SM_ele_disc_phone_01, SM_ele_lamp_06, SM_ele_phone_02_a, SM_ele_phone_03_a, SM_ele_phone_03_b, SM_ele_phone_03_c, SM_ele_phone_03_d, SM_ele_radio_1, SM_ele_tube_radio_01, SM_ele_tube_radio_02, SM_ele_wall_lamp_02, SM_ele_wall_lamp_02_a, SM_ele_wall_lamp_02_b, SM_ele_wall_lamp_02_c, SM_elm_Reactor_02_b_1, SM_elm_Reactor_02_c_1, SM_elm_Reactor_02_d_1, SM_foo_apple_01_a, SM_foo_baked_potato_01_a, SM_foo_beetle_01_a, SM_foo_beetle_01_b, SM_foo_box_01, SM_foo_bread_01_i, SM_foo_carrot_01_a, SM_foo_carrot_01_b, SM_foo_carrot_01_c, SM_foo_cookies_01_a, SM_foo_cookies_01_d, SM_foo_cookies_01_g, SM_foo_cookies_01_j, SM_foo_cucumber_01_a, SM_foo_garlic_01_a, SM_foo_mandarin_01_a, SM_foo_nut_01_a, SM_foo_onion_peel_01_a, SM_foo_onion_sack_01_closed, SM_foo_potato_01_b, SM_foo_potato_01_c, SM_foo_salted_cucumbers_c, SM_foo_sausage_01_e, SM_foo_sausage_01_f, SM_foo_squash_01_01_a, SM_fur_FoldingChair_01_a_1, SM_fur_FoldingChair_01_b_1, SM_fur_bar_chair_01_a, SM_fur_bar_chair_01_b, SM_fur_bar_chair_01_c, SM_fur_fan_02, SM_fur_furniture_old_chair, SM_fur_furniture_pack_01_02_a, SM_fur_furniture_pack_01_02_b, SM_fur_furniture_pack_01_04_c, SM_fur_hospital_cart_01, SM_fur_kinder_bed_03_c, SM_fur_kinder_garden_01_d, SM_fur_kinder_garden_01_e, SM_fur_kitchen_furniture_01_a, SM_fur_kitchen_furniture_01_b, SM_fur_school_chairs_01_a, SM_fur_school_chairs_01_b, SM_fur_school_chairs_01_c, SM_fur_school_chairs_01_d, SM_fur_screw_chair_01_a, SM_fur_screw_chair_01_b, SM_fur_table_09_stool_01, SM_gar_ban_clothes_01_o, SM_gar_ban_clothes_01_q, SM_gar_bottle_03, SM_gar_bottle_04, SM_gar_burned_barrel_01_b, SM_gar_cloth_02_l, SM_gar_cloth_02_m, SM_gar_cloth_02_n, SM_gar_kindergarden_cubes_01_kindergarden_cubes_01_arch_1, SM_gar_kindergarden_cubes_01_kindergarden_cubes_01_arch_2, SM_gar_kindergarden_cubes_01_kindergarden_cubes_01_brick_1, SM_gar_kindergarden_cubes_01_kindergarden_cubes_01_brick_4, SM_gar_kindergarden_cubes_01_kindergarden_cubes_01_cone_1, SM_gar_kindergarden_cubes_01_kindergarden_cubes_01_cone_4, SM_gar_kindergarden_cubes_01_kindergarden_cubes_01_cube_1, SM_gar_kindergarden_cubes_01_kindergarden_cubes_01_cube_2, SM_gar_kindergarden_cubes_01_kindergarden_cubes_01_triangle_2, SM_gar_kindergarden_cubes_01_kindergarden_cubes_01_triangle_3, SM_gar_metall_01_01_01, SM_gar_metall_01_03_10, SM_gar_metall_01_03_11, SM_gar_toy_bear_01_a, SM_gar_toy_bear_01_b, SM_gen_abacus_01, SM_gen_ball_01, SM_gen_ball_01_dm, SM_gen_bicycle_01_c, SM_gen_bicycle_01_d, SM_gen_bicycle_01_f, SM_gen_bicycle_01_g, SM_gen_bicycle_wheel_01, SM_gen_big_bottle_01_a, SM_gen_books_01_01, SM_gen_books_01_02, SM_gen_books_01_03, SM_gen_books_01_04, SM_gen_books_01_05, SM_gen_books_01_06, SM_gen_books_01_07, SM_gen_books_01_08, SM_gen_books_01_09, SM_gen_bottle_crate_01, SM_gen_bowels_01, SM_gen_bowels_01_a, SM_gen_bowels_01_b, SM_gen_bowler_hat_01_a, SM_gen_buckets_1_1, SM_gen_buckets_1_2, SM_gen_buckets_1_3, SM_gen_buckets_1_4, SM_gen_can_1_base, SM_gen_can_1_cap, SM_gen_cardboard_box_01, SM_gen_cardboard_box_02, SM_gen_cardboard_box_03, SM_gen_cardboard_box_04, SM_gen_cardboard_box_05, SM_gen_cardboard_box_06, SM_gen_ceramic_cups_01_a, SM_gen_ceramic_cups_01_b, SM_gen_ceramic_cups_01_c, SM_gen_ceramic_cups_01_f, SM_gen_ceramic_cups_01_j, SM_gen_ceramic_cups_01_n, SM_gen_ceramic_cups_01_q, SM_gen_ceramic_cups_01_r, SM_gen_ceramic_cups_01_s, SM_gen_chair_dam_01_a, SM_gen_chair_dam_01_b, SM_gen_chair_dam_01_c, SM_gen_chair_dam_01_d, SM_gen_chair_dam_01_e, SM_gen_child_toys_01_a, SM_gen_child_toys_01_b, SM_gen_child_toys_02_a, SM_gen_child_toys_02_b_01, SM_gen_child_toys_02_c, SM_gen_chrismas_toys_01_a, SM_gen_chrismas_toys_01_b, SM_gen_chrismas_toys_01_c, SM_gen_chrismas_toys_01_d, SM_gen_chrismas_toys_01_e, SM_gen_dolls_01_a, SM_gen_dolls_01_b, SM_gen_dolls_01_c, SM_gen_dolls_01_d, SM_gen_dolls_01_e, SM_gen_dolls_01_f, SM_gen_explosive_barrel_01_a, SM_gen_explosive_canister_01_a, SM_gen_fire_shield_01_b, SM_gen_fire_shield_01_c, SM_gen_gas_cylinder_01_01, SM_gen_gas_cylinder_01_02, SM_gen_gas_cylinder_01_03, SM_gen_gas_cylinder_01_04, SM_gen_gas_cylinder_01_05, SM_gen_kinder_pot_01_a, SM_gen_lamp_illich_01_a, SM_gen_loot_metalcrate_dm, SM_gen_mugs_metal_1_1, SM_gen_mugs_metal_1_2, SM_gen_mugs_metal_1_3, SM_gen_mugs_metal_1_4, SM_gen_parcel_01_a_solid, SM_gen_parcel_01_b_solid, SM_gen_parcel_01_c_solid, SM_gen_plant_pot_02_a, SM_gen_plant_pot_02_c, SM_gen_plant_pot_02_e, SM_gen_plastic_barrel_01, SM_gen_plates_01_a, SM_gen_plates_01_e, SM_gen_plates_01_f, SM_gen_plates_01_l, SM_gen_plates_01_n, SM_gen_plates_01_o, SM_gen_rusty_barrel_01_b, SM_gen_rusty_barrel_01_f, SM_gen_teapots_01_a_1, SM_gen_teapots_01_b_1, SM_gen_teapots_01_c_1, SM_gen_teapots_01_d_1, SM_gen_toolbox_01, SM_gen_wheelbarrow_01_wheel, SM_int_metal_sheet_01_a, SM_int_metal_sheet_01_b, SM_int_woodbox_01_a, SM_int_woodbox_01_b, SM_int_woodbox_01_c, SM_int_woodbox_01_d, SM_int_wooden_planks_01_a, SM_int_wooden_planks_01_b, SM_int_wooden_planks_01_c, SM_int_wooden_planks_01_d, SM_int_wooden_planks_01_e, SM_int_wooden_planks_01_f, SM_lab_Medical_equipment_10, SM_lab_Medical_equipment_12, SM_lab_Medical_equipment_3, SM_lab_Medical_equipment_4, SM_lab_Medical_equipment_5, SM_lab_enema_01_b, SM_lab_med_box_01_a, SM_lab_med_box_01_b, SM_lab_med_plate_01_a, SM_lab_med_plate_01_b, SM_lab_med_sterilizer_01_a, SM_lab_med_sterilizer_01_b, SM_lab_med_sterilizer_01_c, SM_mil_ammo_box_01, SM_mod_con_des_01_07_ForMovable, SM_mod_con_des_01_08_ForMovable, SM_mod_con_des_03_22_1_ForMovable, SM_too_gaswrench_1, SM_too_screwdriver_01_a, SM_too_screwdriver_01_b, SM_too_tools_01_c, SM_too_tools_01_d, SM_too_tools_01_e, SM_too_tools_01_f, SM_too_tools_01_h, SM_too_tools_01_i, SM_too_tools_01_k, SM_too_tools_01_l, SM_uni_bun_props_01_c, SM_uni_nii_box_01_a, SM_uni_nii_box_01_b, SM_uni_nii_chair_02, SM_uni_nii_dishes_e, SM_uni_nii_monitor_01_a, SM_uni_nii_monitor_01_b, SM_uni_nii_server_c, SM_uni_nii_server_d, SM_uni_nii_sign_03_a, SM_uni_nii_sign_03_b, SM_uni_nii_sign_03_c, SM_uni_nii_table_stuff_03_a, SM_uni_nii_table_stuff_03_b, SM_uni_nii_table_stuff_03_c, SM_uni_nii_table_stuff_03_e, SM_uni_nii_table_stuff_03_f, SM_uni_nii_table_stuff_03_g, SM_uni_nii_trashcan_02, SM_uni_nii_working_chair_01_a, SM_uni_nii_working_chair_01_b, SM_uni_nii_working_chair_01_c, SM_uni_nii_working_chair_01_d, SM_uni_nii_working_chair_01_e, SM_veh_btr70_wheel_tire, SM_veh_generator_tire_01, SM_veh_hvytruck01_tire, SM_veh_offrv_001_tire, SM_vil_basket_01_a, SM_vil_basket_01_b, SM_vil_basket_01_c, SM_vil_basket_01_d, SM_vil_bidon_1, SM_vil_cans_01_01, SM_vil_cans_01_03, SM_vil_cans_01_04, SM_vil_cans_01_06, SM_vil_cans_01_07, SM_vil_cans_01_08, SM_vil_cans_01_10, SM_vil_cans_01_11, SM_vil_cans_01_13, SM_vil_cans_01_14, SM_vil_cans_01_16, SM_vil_cans_01_18, SM_vil_cans_01_19, SM_vil_cans_01_20, SM_vil_cans_01_22, SM_vil_cans_01_23, SM_vil_cans_01_24, SM_vil_cans_01_25, SM_vil_cans_01_26, SM_vil_cans_01_27, SM_vil_cart_wooden_01_b, SM_vil_kazan_01, SM_vil_kazan_cup_01, SM_vil_table_03, SM_vil_tools_axe_1_grip, SM_vil_tools_axe_2_grip, SM_vil_tools_hammer_1_grip, SM_vil_tools_hammer_2_grip, SM_vil_utensil_pack_01_a, SM_vil_utensil_pack_01_c, SM_vil_utensil_pack_01_d, SM_vil_village_tools_hoe, SM_vil_village_tools_pitchfork, SM_vil_village_tools_scythe, SM_vil_village_tools_shovel, SM_vil_zinc_basin_01_a, SM_vil_zinc_basin_01_b
- `s2u_dlg_header.tsv`: answerVar, answers, folders, stats, text
- `s2u_qdrop.tsv`: D, stats, v
- `s2u_qitems.tsv`: S, norm, pos, skip, stats, v
- `s2u_qpick.tsv`: pin, stats
- `s2u_vendor.tsv`: n, protos, rows
- `flags_s2core.tsv`: abpguard, abpmax, abpmax3, abpsec, acache, acneg, aimask, aiwatch, aiwatchm, aiwatchs, alifeguid, alifekeephubs, alifekeepquest, alifeoff, alifetrader, anomcd, anomr, anomsync, artclass, artcool, artmax, artmute, artnear, artquiet, artrad, artradius, artreach, artsync, autoload, avgain, avlead, b164off, bodyoffdestroy, bodysafe, bodywait, campaign, cfall, cfallm, cfallsec, cfollow, cfollowlift, cfollowm, cfollowstep, choice, cine, cinedlg, cinefollow, cinefreeze, cinegod, cinehold, cineinput, cinejump, cinelog, cinemax, cinesleep, cinetest, cjcool, cjoff, cjoin, cjoinm, clammo, clcopy, clgone, clholdmax, cllease, cllog, clmax, cloot, clr, clrc, clsend, clsid, clvis, corepuppet, coretarget, cpammo, cpdelay, cpequip, cpersist, cpper, cpsecs, cptest, csave, cscalm, csconfirm, csdelay, csold, csretry, cssecs, cssettle, cssteps, cstimer, cswait, cswc, ctrig, dmgap10, dmgcap, dmgdown, dmgfloor, dmgin, dmgmax, dmgmin, dmgmode, dmgscale, dmgspawn, dmgtest, dmir, dmirblk, dmirclick, dmirend, dmirint, dmirkeep, dmirnpcm, dmirstart, dmirtxt, dmirwait, dobj, dobjexp, dobjfx, dobjfxmax, dobjgen, dobjhold, dobjmiss, dobjr, dobjsec, dobjstat, doorhold, doorr, doorre, doors, doorsec, downfreeze, downhp, downmsg, downsecs, emgrace, emparkpup, emprotect, emreset, emretry, emskew, emstart, emstopgap, emsync, emtest, emwait, farbody, ffc, ffcttl, ffcwin, fpscap, fpsenemy, fpsfe, fpsother, fpsver, ftfly, ftfollow, ftgrace, ftjump, ftkeep, ftleash, ftmaxage, ftnear, ftoff, ftpawn, ftqmax, ftrad, ftsettle, ftwait, ground, gsnap, hcblk, headmax, headsafe, hidnpc, hidnpcd, hidnpchp, hidnpcvia, hostcfg, iactlog, iaecho, iaface, iafind, iahold, iainj, ialift, iamax, iamir, iapress, iaq, iareach, iaset, iaunk, icmax, icontr, idrop, idropm, idropr, ien, ienanim, ienhatch, ienhold, ienlamp, ienprompt, ienr, iensec, ientab, ientoggle, inodes, ionly1, ipr, iprobe, isame, itake, itest, joinm, joinport, keyfix, keytol, killz, kit, kitdelay, kitwait, kzsafe, kztop, kzxy, ldblk, ldblkr, ldclose, ldhold, ldkill, ldsave, ldsavekeep, ldsavew, ldtrig, ldwatch, ldwatchs, lead, leashown, leashpullwin, lifeguard, lockfirst, locks, locktest, loot, lootr, lootreq, lootshare, lscont, lscr, lsctake, lscwait, lsnog, lsper, lsr, meshsafe, mqpull, mqwin, mshys, mslot, mslotsec, mslr, msstay, n3cache, n3id, n3kill, n3max, n3r, n3trig, n3ur, n3use, n3usesec, n7, n7conf, n7eq, n7per, n7poll, n7shared, n7sv, n7svdir, n7svloc, n7wait, ndgrace, ndhp, ndleash, ndmoney, ndnear, ndresphp, ndtest, ndwait, netlockkeep, netrel, netrelhold, netrelmax, netrelper, netrelseen, newgame, newgamesecs, nodeath, nopause, npcsync, npmax, npsai, npsanim, npsbud, npsd, npsdlghold, npsdlgr, npsidle, npskey, npslist, npslog, npslost, npsmatch, npsmax, npsmode, npsmove, npsmr, npsmstop, npsr, npssnap, npsstill, npsv, npwait, nrdoor, nsbhold, nsbmax, nscap, nsdead, nsgain, nsip, nsipmax, nsippad, nslog, nsmax, nsmooth, nsnoback, nssnap, nsuro, nsvmax, nsyaw, nsyawgain, offtick, orphmax, orphrm, orphsave, orphsec, orphsweep, orphvia, pabh, pafall, pahold, pamaxr, patrn, peersilent, ptake, pupabpstill, pupadopt, pupadoptr, pupai, pupaimax, pupais, pupanim, pupanimbp, pupanimfix, pupback, pupcmoff, pupfar, pupfeet, pupfix, pupfixcm, pupfixmax, pupfixn, pupmove, pupmvcr, pupmvdead, pupmvgain, pupmvgainz, pupmvlog, pupmvmode, pupmvrm, pupmvslot, pupmvsnap, pupmvsprint, pupmvtag, pupmvvmax, pupnoai, pupnogun, pupnoreinit, pupretry, pupweapon, pupwin, pwrescan, pwscan, pwsnap, qbootdedupe, qbootwin, qcatchup, qdead, qdiv, qdivfix, qdivj, qdivkeep, qdivlog, qdivm, qdivn, qdivroll, qdivs, qdrop, qdropfn, qdrophold, qdropwin, qextra, qfall, qfalldz, qfallr, qfallup, qfallwin, qgap, qigive, qimirror, qiper, qir, qire, qirm, qisec, qitem, qlsettle, qmload, qmloadw, qmre, qmrmhost, qmset, qnkeep, qnode, qnodlg, qnohold, qnsrc, qonce, qpick, qpkeep, qplead, qplkeep, qpmax, qpwait, qrbdelay, qrbmax, qrbmode, qrbnl, qrbwindow, qrelay, qreward, qrollback, qskipcatch, qsync, qtest, qworld, relfoe, relmir, relmirr, relmirs, relmirtol, repecho, repechocd, repfoe, repsync, resend, revivehp, reviveradius, revivesecs, revwait, rvder, rwtest, shotattr, shotlag, shotpad, sleepans, sleepcool, sleepfight, sleepkeep, sleepmaxage, sleepmode, sleepnat, sleeppull, sleeppullr, sleeprate, sleepskip, sleepsync, sleepvirt, sleepwait, smooth, smoothgain, smoothlog, smoothsnap, spawngap, ssbox, ssdelay, ssremove, ssstrict, sstash, sxjoin, sxsave, sxtries, sxwait, taken, takenown, tgtcalm, tgtdiag, tgtgod, tgtgodwait, tgtnofall, tgtnoint, tgtpark, tgtsafe, tgtwaitmax, tpdrop, tpfback, tpfit, tpfloor, tpfring, tpfwait, trigmargin, trignear, trigre, trigself, trradius, trwindow, tsync, vendmir, vendone, vendr, vendtr, vendtrade, wsfx, wshot, wsmax, wsnmax, wsr, wvface, wvmaxn, wvoice, wvspk, wvsw, wxfollow, wxinstant, wxlock, x1c
- `flags_main.tsv`: anim, autobridge, autocontinue, autowalk, avatar, avatarmode, avdebug, avground, avoffx, beacon, clientalife, compvel, ctrlrot, diag, difficulty, disablemove, god, godlayers, godtest, godtoggle, headfix, hz, leashm, look, lookdiag, luacmd, maxdist, maxnpcs, mirrors, mirrorspread, mirrortest, nodamage, npcdmg, npcdmgtype, playergod, prof, readopt, revalidate, rotate, scan, scanage, scanmove, scanr, scanself, settime, shotdetect, shotdmg, shottest, syncgap, syncthresh, synctime, synctimetest, syncweather, velwrite, wxtest
- `weapons_main.tsv`: SK_AK74, SK_Fora230, SK_Gp3a, SK_Skp, SK_ThreeLine, SK_Toz34, SK_aku, SK_apb, SK_bucket0, SK_d1200, SK_dnipro, SK_fora0, SK_gauss, SK_gp37, SK_grim0, SK_gvi, SK_integ, SK_kharod000, SK_kora, SK_lav, SK_m1000, SK_m160, SK_m701, SK_m86000, SK_mar, SK_obrez, SK_pkp00000, SK_pm, SK_ram2, SK_rhino00000, SK_rpg7, SK_spsa00, SK_svm, SK_svu, SK_udp, SK_vip, SK_zubr0, Sk_arev
- `diff_weapon_mult_main.tsv`: Easy, Hard, Medium, Stalker

### Not converted (plan says drop or code)
- `s2u_dlg.lua` key `set` (per-node dialog table): DROP (PORT_PLAN 1c). Header keys are in `s2u_dlg_header.tsv`.
- `s2u_interact.lua`, `s2u_items.lua`: DROP (ia71 and idrop are OFF).
- `dm70.lua`, `cj68.lua`, `ia71.lua`: code, not data (ported by hand or deleted).
- `dm70.lua` `M.FLAGS` (dlg* flags, line 184): not converted here.
- Already TSV and kept as they are: s2u_triggers, s2u_cont, s2u_contk, s2u_equip, s2u_trade, s2u_art, s2u_artspawn, s2u_kit, s2u_basekit.txt.

### Column meaning per file

The source comment lines are copied from each Lua file (they describe the key meaning):

#### s2u_actions.tsv
    -- generated by b68/gen_action_table.py from the user's install; do not edit
    -- rule: click = replay the real click handlers (state-checked), explicit = call on/off, native = SetEnabled only

#### s2u_anomaly.tsv
    -- generated by b73items/gen_b73.py from the user's install; do not edit
    -- anomaly BP class -> trigger radius r / collision height h (cm, before actor scale), cooldown cd (s), native class n; rule once only

#### s2u_choice.tsv
    -- s2u_choice.lua: GENERATED by b91choice/gen_choice.py (user rule N3: story choices outside dialogs stay with the host). Do not edit.
    -- npc[guid] = {x,y,z,tier,squad} placeholder position (0,0,0 = none), tier 1 clear choice / 2 cancels a path, squad 1 = squad guid: NPCs whose death/hit/hostility is a quest branch -> no client damage
    -- use[guid] = 1 usable (lever/switch/terminal/signal sender): the client cannot use it, the host never applies its change; 2 = NPC/container/corpse/item (other channels, report)
    -- trig[sid] = tier (1 clear choice / 2 cancels a path): relayable (#QN) quest triggers that branch -> the host never fires them for the client
    -- item[sid] = 1: get/lose-item listeners that branch (report only; the qitem channel decides items)

#### s2u_cine.tsv
    -- generated by b68/gen_cine_table.py; scene SID -> {kind, tp_first, s2c}; cause SID -> scene SID

#### s2u_destruct.tsv
    -- generated by b74world/gen_destruct_table.py from the user's install (DestructibleObjectPrototypes); do not edit
    -- key = OriginalMesh short name (the actor's StaticMeshComponent mesh); k = destroy|mesh|explode|physics|fx|movable

#### s2u_dlg_header.tsv
    -- generated by gen_dlg_table.py (b70) from the user's install; do not edit
    -- bits: 1 StartForcedDialog, 2 CanExitAnytime, 4 CallPlayer, 8 SeekPlayer

#### s2u_qdrop.tsv
    -- generated by D:/modding/offline/b130qdrop/gen_qdrop.py from the Zone Kit + the installed s2u_qitems.lua; do not edit
    -- D[sid] = 1: a stock quest item (IsQuestItem true) that the pak zzzzzz_S2CoopQuestDrop_P can switch: S2QD0_<sid> (droppable),
    -- S2QD1_<sid> (back to quest item). Items not listed keep the stock rule.

#### s2u_qitems.tsv
    -- generated by D:/modding/offline/b87qitem/gen_qitems.py from the Zone Kit; do not edit
    -- S[sid] = count the quest needs (host keeps at most this many from relays); skip[node] = ItemAdd node the client never replays;
    -- pos = placeholders (corpse/container) that can hold a quest item: {x, y, z (cm), guid, type, sids}

#### s2u_qpick.tsv
    -- generated by gen_qpick.py (b99qpick) from the Zone Kit quest graph; do not edit
    -- pin[SetDialog SID][k] = nodes pin k launches, space separated; '!' = Excluding launcher (the pin cancels that node)

#### s2u_vendor.tsv
    -- s2u_vendor.lua (b78fix gen_vendor.py, game data): every placed vendor NPC (trader/medic/bartender/technician). Positions in cm.

Block tables (flags, weapons) have no comments of their own: `k1` = key name (`flags_*`: flag name, value in `v`), `weapons_main`: `k1` = weapon mesh key (e.g. `SK_pm`), `k2` = index 1..5 (BaseDamage, ArmorPiercing, EffectiveFireDistanceMax cm, DistanceDropOffLength cm, MinBulletDistanceDamageModifier), `diff_weapon_mult_main`: `k1` = difficulty name.

---

<a id="nola-docs-release"></a>

## Release process

The release ships `main.dll`, the pak, UE4SS and one `flags.txt` in `C:\nola_bridge`. Nothing else. Every table the DLL reads at runtime must be inside the DLL. A table that only exists in a dev bridge folder (`C:\s2coop_inst\*`, `C:\nola_inst\*`) works in every dev test and is empty for every player (RC1: no container tables, the stash window closed itself, ST3 §352; no start kit, equipment, artifact or trader tables, RT4).

### The list: `data/nola_runtime.tsv`

One row for every file the DLL opens and every dev-only flag.

| column | meaning |
|---|---|
| kind | `file` or `flag` |
| name | file name in the bridge folder (`*` allowed for generated names) or flag key |
| class | `a` table that must ship (embedded), `b` state the mod or the installer writes, `c` dev or debug only (never in a release DLL) |
| where | reader (file and function) |
| rows | always empty (kept for older checkers); counts are taken from the table itself at check time |
| marker | class c only: strings that must not be in a release DLL, `w:` UTF-16, `a:` ASCII |
| note | what breaks without it |

### Adding a runtime-read table

1. Put the file in `data/`.
2. Add a `file <name> a <reader>` row to `data/nola_runtime.tsv`.
3. Run `uv run --no-project python -I tools/gen_x0_data.py --rc`. It checks the list and rewrites `src/s2x_data.rc` (RCDATA, one entry per class a row).
4. Read it with a bridge-first reader: `x0::table(name, out)` (bridge file, then the embedded copy), or the module `readText` (items, save), `readFile` (pop), `data` (quest, world) or `x0::data` / `x0::data_tsv` (embedded first). Never open a table with a plain bridge path.
5. Rebuild and run the x0 suite.

Order of `x0::table`: the bridge file wins when it exists (dev override, per-PC copy); otherwise the embedded copy (flag `taball`, default 1; 0 = bridge only, the RC1 behaviour). `tabText` in s2m_items is the same order for the container tables (flag `contall`).

### Dev-only inputs and flags (class c)

Dev inputs (`role.txt`, `state.json`, `s2cmd.txt`, `relay_record.txt`, the `s2x_data\` loose override) are compiled only when `S2X_RELEASE` is off. A release build (`S2X_RELEASE=ON`) locks every class c flag to its default: flags.txt, `fset` and the host cannot turn them on. A new dev input gets a class c row with a marker and an `#ifndef S2X_RELEASE` guard.

### Tests

- x0 suite, `test_x0.exe`: every class a table loads with at least one row from the embedded copy with an EMPTY bridge folder; every embedded resource is listed; the bridge copy wins; `taball=0` reads the bridge only.
- x0 suite, `test_rel.exe` (built with `/DS2X_RELEASE`): the same table check, dev flags locked, the loose override ignored.

### Builder check

`ModWork\s2coop\tools\build_release_cpp.py` runs `check_release_tables.py` on the release DLL (also in `--check`). The build FAILS and names the file and this list when:

- a file name the source reads is not in `data/nola_runtime.tsv`;
- a class a table is missing from `data/`, from `src/s2x_data.rc`, or is not byte-identical in the DLL (and is not the shipped `flags.txt`);
- the DLL is not an `S2X_RELEASE` build, or a class c marker is in the DLL;
- a test/diagnostic flag of the builder is not a class c flag row.

Standalone: `uv run --no-project python -I <ModWork>\s2coop\tools\check_release_tables.py --dll <dll> --repo <repo>`.

### Fix checks run the release build

Build the release DLL with `tools\wt.ps1 build <name> -Release` (`S2X_RELEASE=ON`, copied to `cppbuild\Release\NolaNative.dll`). The next build without `-Release` switches `cppbuild\Output` back to the dev DLL. A fix that touches a table, the bridge or a dev input is checked offline with the release DLL, `check_release_tables.py` and an empty bridge folder, not only with a dev bridge.

---

<a id="nola-docs-steam-design"></a>

## Steam design

Goal: two players connect through Steam. Nobody types an IP, needs a VPN or forwards a port. The host invites a Steam friend, or the friend uses Join Game in the Steam friends list. The IP/UDP route (R1, `netpeer`) stays as the other option and as the fallback.

### 1. Recon (evidence)

| Fact | Evidence |
|---|---|
| Steam API dll | `<G>\Engine\Binaries\ThirdParty\Steamworks\Steamv157\Win64\steam_api64.dll`: FileVersion 06.91.21.57 (SDK 1.57), md5 500475b2…, 1059 exports. No steam_api64 in `Stalker2\Binaries\Win64`. AppID 1643320 is in `Stalker2\Binaries\Win64\steam_appid.txt`. |
| How the exe uses it | Stalker2-Win64-Shipping.exe (md5 a4fc3575…, PE 5.5.4.0) DELAY-imports steam_api64.dll. Imports: GetHSteamUser, Init, RestartAppIfNecessary, RunCallbacks, Register/UnregisterCallback, Register/UnregisterCallResult, Shutdown, SteamGameServer_*, SteamInternal_*. No ManualDispatch import. The exe uses no SteamNetworkingMessages or Sockets, only the old "SteamNetworking006" string. |
| Who initialises and pumps | SteamAPI_Init is called in FUN_146d43708 (SteamShared FSteamClientInstanceHandler, which logs "SteamAPI initialized"). The only RunCallbacks call is in FUN_146d467bc (FOnlineAsyncTaskManagerSteam::OnlineTick): `call qword ptr [0x149f0d170]` (delay IAT slot in .data, RW), guarded by bSteamworksClientInitialized. |
| Steam is up in practice | The crash contexts in `%LOCALAPPDATA%\Stalker2\Saved\Crashes` list steam_api64.dll loaded and a thread "OnlineAsyncTaskThreadSteam DefaultInstance". So OSS Steam is initialised and pumps the legacy callbacks on its own thread. |
| Callbacks the game registers | 333 GameLobbyJoinRequested (size 16), 337 (264), 504 LobbyEnter (24), 505, 506 (32), 331, 304 and others (b_006d7.c; sizes from vtable slot 2 at 0x148eed3a0..). |
| steam_api64 dispatch internals (disassembly) | RegisterCallback inserts into a std::multimap without a lock. Object layout: vptr@0, flags@8 (bit 0 registered, bit 1 game server), id@0xc. Callbacks are dispatched through vtable[1] = Run(void*). Call results: size from vtable[2], then vtable[0] = Run(p, io, hCall). The dll reads the id at +0xc for call results too, so the id must be set. |
| Unexpected LobbyEnter in UE OSS | UE OSS Steam only logs "Entered lobby %s, but not found in sessions list". It does not LeaveLobby. It also parses `+connect_lobby` itself (CheckPendingSessionInvite). |
| Needed flat exports | All present in the 1.57 dll. SteamUser is v021 (no v023 flat export), Friends v017, Matchmaking v009, Utils v010, NetworkingMessages v002, NetworkingUtils v004. |
| Other stores | No GOG or Game Pass copy on this PC. The route is Steam-only: a copy without the dll falls back to ip after `netsteamwait`. |
| Bandwidth to carry | C:\s2coop_inst relay.log: host sends median 62 KB/s, p95 72.5 KB/s, largest datagram 3921 B; client about 3 KB/s. |
| Unknown (live only) | What the game does with the OSS invite-accepted delegate or with `+connect_lobby`. Whether the Steam launcher passes `+connect_lobby` to the shipping exe. Whether SDR carries 62-72 KB/s without loss. Exact LobbyCreated_t size (16 is from the SDK; not seen in the binary). Thread safety of Matchmaking calls made from the OSS thread (that is the thread the game itself uses for them). |

### 2. Design

The simplest design that leaves s2r_net.cpp (R1) untouched:

```
game relay (s2r::Net) 127.0.0.1:listen  <-UDP loopback->  shim 127.0.0.1:ephemeral  <-ISteamNetworkingMessages (SDR)->  peer shim  <-loopback->  peer relay
```

- **Loopback shim.** `steam_route` sets the relay's peer to `127.0.0.1:<shim port>`, so Net binds 127.0.0.1 only (no firewall rule, no Windows prompt). The shim forwards each datagram's exact bytes as one Steam message: flags 33 (UnreliableNoNagle | AutoRestartBrokenSession), channel 0. It adds no framing. Datagrams that come back are written to the relay's port. relay_v2 stays end to end, including the save transfer.
- **Pump hook.** The shim never calls Matchmaking, Friends, User, Utils or callback (un)registration from its own thread. Those go through a trampoline written into the exe's own `SteamAPI_RunCallbacks` import slot (found generically by walking delay imports, then normal imports). It runs our pre-pump on the game's Steam thread, then the real RunCallbacks. This avoids the unlocked multimap race and keeps every call on the thread the game already uses. The slot is written only after the game has bound it (`*slot == GetProcAddress(RunCallbacks)`), so the delay-load helper can never overwrite it. The shim thread only calls the NetworkingMessages and Identity functions.
- **Callbacks without stealing.** These are legacy callback objects (`CbBase`, same vtable as CCallbackBase). The dll multicasts each callback to every registered object, so the game's own handlers still run.
- **Host.** When Steam is ready (GetHSteamUser != 0, interfaces present, BLoggedOn), the host creates a friends-only lobby, max 2, with lobby data `nola=2`. The peer is the other lobby member, polled every 0.5 s. The Home key opens ActivateGameOverlayInviteDialog. A friends-only lobby shows "Join Game" in the friends list and raises GameLobbyJoinRequested on the friend (documented GameLobbyJoinRequested_t behaviour). No rich presence.
- **Client.** It joins on 333, or on `+connect_lobby <id>` / `-connect_lobby <id>` in GetCommandLineW. On LobbyEnter it checks the response, `nola=2` and that another user owns the lobby; otherwise it leaves. It goes back to waiting when the host leaves or ownership moves to itself.
- **Sessions.** Sending implicitly accepts. A SessionRequest (1251) is accepted only for the lobby peer. Others are logged ("not accepted: not the lobby peer") and expire after 30 s. Messages from anyone but the peer are dropped and counted (`foreign`). Loopback datagrams from any port other than the relay's are dropped (`local_foreign`).
- **Fallback.** Flags `net=steam|ip` (default steam) and `netsteamwait=60`. If steam_api64 is never loaded, the slot is never bound or pumped, or the user is not logged on within the wait, the link fails once. It logs "<reason>: using the IP route instead" and restarts the relay on `netpeer`. A change to `net` or `netsteamwait` retries. `net=ip` never touches Steam.
- **Stop.** The shim thread is joined. The pump thread is asked to unregister everything and leave the lobby (up to 2 s), then the slot is restored and in-flight trampolines are drained. If the game stopped pumping, the callback objects are left registered but inert (never freed), so a later dispatch is safe.
- **Dev PCs.** Two instances on one PC have the same Steam account, so the lobby cannot pair them: dev flags must set `net=ip`.

### 3. Files

- `src\s2r_steam.h`, `src\s2r_steam.cpp`: the Link (shim, pump hook, lobby state machine, sessions). It has no x0 or UObject dependency.
- `src\s2r_steam_x0.cpp`: x0 glue. `steam_route(Config&)`, `steam_stop`, `steam_invite`, the Home key, the `steam` command (status | invite | join <id> | leave), the status line, and on_flag for net / netsteamwait.
- `tests\steam\patch_s2r_x0.py`: the four-line hook into s2r_x0.cpp (not applied; integration step).
- `tests\steam\fake_steam_api.cpp`, `fake_backend.h`, `fake_world.h`: a fake steam_api64.dll that reproduces the dll's raw dispatch (vtable[1] for callbacks; vtable[2] then vtable[0] for call results; flags/id checks), session-request semantics, and a lobby world.
- `tests\steam\steam_test.cpp`, `glue_steam_test.cpp`, `build_test.bat`, `out\steam_result.txt`, `out\glue_result.txt`.
- `tests\steam\LIVE_TODO.md`: the live checks.

### 4. Status line and logs

`steam <state> self lobby peer(name) port sent recv foreign nopeer send_err last_err sess_ok sess_rej pumps`. The states are waiting_for_steam, creating_lobby, hosting, waiting_for_invite, joining, joined and failed. All log lines start with `S2NET steam: `, and the route choice is logged as `S2NET route: steam|ip (...)`.

---

<a id="nola-tests-a2-slide-design"></a>

## A2 slide design

Symptom: client NPC copies sometimes slide (body translates, legs idle) instead of walk/run.

### 1. Copy movement paths on the client

| Path | Who | Placement | CMC | Leg source | Legs? |
|---|---|---|---|---|---|
| natkin (b182) | s2n_nat.cpp kin_frame 4240-4314 from tick_cb 4315 | K2_SetActorLocationAndRotation at host sample now-natkind(100ms) | tick ON; RequestedVelocity +0x578 + bit +0x54C (bit0 bHasRequestedVelocity, bit1 bRequestedMoveWithMaxSpeed) when speed>20 (4286-4303); MaxWalkSpeed +0x268 = speed*1.1 | PoseSearchLocomotion motion matching: trajectory from RequestedVelocity, database/tag from AI move tag U+0x6c8 (U=[agent+0xac8], FUN_142508b2e 422-547, "%s.MoveBehaviourTransition") | yes while AI MoveTo goal alive with gait 2/3/4 (natkinord=1, natrun 230, natsprint 450) |
| npcsync mover (b122/b125, npsmode 2) | s2m_npcsync.cpp np_take 833-904, np_drive 922-1004 | PMC mover (m01::mover_seed/sample/drive) | brain StopLogic, TogglePathFollowingComponent(false), StopMovementImmediately, CMC SetComponentTickEnabled(false); Velocity CMC+0xC0 / Acceleration +0x318 written; re-check every 1 s that CMC stays off | none (no clip, Montage_Stop on take) | NO: VERIFIED NOT-WORKING (CMC tick off + Velocity writes = legs idle, foot slip 0.29-0.78; b150 v2 anim_movimento 0/83) |
| natnpc non-kin (soft / vend) | s2n_nat.cpp drive 3692-3830 | snap/nudge, MaxWalkSpeed, face | on | AI MoveTo | yes (not the slide source in logs: empurroes=0 under kin) |

Other CMC writers checked (s2m_bodies puppet only, s2m_damage player, s2m_travel/save): none touch natnpc copies.

### 2. Root (proven from logs + code)

R1: two owners for one body. natnpc and npcsync hand the same client body back and forth; while npcsync owns it
the CMC tick is off and the PMC mover slides it.

Evidence, client UE4SS.log 17:25-17:41 (L1 session), host uid 1486 (_2147479889), body BP_AI_Human_C_2147448468, npcsync takes #14-#19:
- natnpc release (natlost 3 s, s2n_nat.cpp 3965-3975) -> npcsync take after 0.1-0.9 s:
  17:33:42.62->43.33, 36:24.03->24.13, 36:43.20->43.62, 37:01.22->02.12, 39:03.62->04.22, 39:22.72->22.93.
- natnpc re-adopt -> npcsync release after 0.03-0.93 s (CMC still off while natkin already places the body):
  34:05.10->.13, 36:26.13->.23, 36:44.41->.63, 37:03.52->04.12, 39:05.72->06.32, 39:25.20->26.13.
- Visible how-4 releases ("fica visivel onde esta, controle devolvido (b169)") then driven by npcsync for minutes:
  2147451765 (host 76991) from 17:29:45.83 (take stopped MG_tp_ar_cover_high); 2147443065 (host 76573)
  17:30:04.98-17:33:29.14 (~3.4 min); 2147448468 17:33:43-17:34:05 (21.8 s).
- Client npcsync 10 s lines: dirigidos=1-2 continuously 17:28:14-17:33:23.
- Races: 17:30:04.98 npcsync took BP_AI_Human_C_2147442348, natnpc CRIADA on the same body 25 ms later;
  17:29:33 natnpc spawned a copy while npcsync drove another kept body for the same host NPC 1486 (two bodies);
  17:28:12 2147474792 (host 75489) on npcsync, natnpc spawned its own copy 17:31:01.

Why the ownership flaps (code):
- Both roles run npcsync=1 (flags_role_client.tsv:62, flags_role_host.tsv:59) with natnpc=1.
- natnpc host list = nearest natmax 8 within natr 6000 of the CLIENT, no hysteresis (host_rebuild 1590-1644).
  npcsync host = within npsr 15000 of EITHER player, budget npsbud 24 / npsmax 16. Host na_lista 3-8 vs npcsync 7-10.
- npcsync exclusion of natnpc bodies is s2nat::listed_addr, checked only on its 1 s pass (np_pair 723-831), so
  a natnpc release is picked up by npcsync at the next pass, and a natnpc re-adopt keeps CMC off until npcsync's
  next pass releases it (np_rel 666-711).
- npcsync hid() = s2m_pop::isHiddenLocal (452); it does not see natnpc set_hidden.
- OFFLINE_REPORT §182 audit item 2 already required npcsync disabled for natnpc-listed NPCs; it is only partly done.

R2 (code-level, not measured): inside natkin the legs need CMC tick on, MovementMode Walking/NavWalking, a live AI
move goal with gait (U+0x6c8 database), RequestedVelocity each frame, and no root-locked montage. Candidate
windows: order start latency (ordem->movimento med 0.21-0.33 s, max 0.40), natkinpin hold goal (MoveTo own point,
3619-3626) while the host moves, order completed before the next one, natgad inert under kin (e.csp = kcsp),
cover montages (A1's area). Log gait stats are consistent (walk host ~110, run ~290; gait-4 rows 1368-1889 are host
velocity spikes). P1 decides whether R2 is real.

Not the cause: natnpc nudges (off under kin, empurroes=0); mirror drops for npcsync NPCs; offanim (ported, s2m_npc.cpp 1557-1616).

Unknown: why host dropped uid 1486 from the natnpc list (natr edge vs other filter) -> P2. Where PerformMovement
consumes +0x54C/+0x590 (no access in the 0x1ddec4 decompile) -> P3 watch.

### 3. Root design (one owner per body, no per-frame override)

D1 natnpc is the only client driver of human copies when natnpc=1:
- cfg npsnat (client, default 0): npcsync client never takes a pawn of class BP_AI_Human* while natnpc=1; host stops
  sending #NP rows for humans. npcsync keeps mutants/others.
- natnpc host list covers every live human within the old npcsync reach the client can see; natmax applies to
  spawning new copies only (cfg natlistall, default 0).
- list hysteresis: keep a listed NPC until natr*1.2 / natlost (cfg natrhys, default 0 = off).
D2 same-frame hand-off when D1 is off or for transitional bodies:
- natnpc take calls the npcsync release for that body in the same frame (CMC tick on, PMC mover_release,
  path following back) via an exported s2m_npcsync release-by-addr (cfg natnpsrel, default 0).
- npcsync np_pair refuses a body listed by natnpc or released by natnpc in the last natlost+2 s (checked at take,
  not only on the 1 s pass).
D3 (only if P1 proves R2): keep the AI move goal alive with the right gait while the host moves; natkinpin hold
goal only when the host speed < 20; re-issue MoveTo before completion (cfg natkinkeep, default 0).

Supervisor 2026-10-17: D1 + D2 approved, D3 only if P1 proves R2. Once D1/D2 are proven live, the switches default
to 1 in the release role TSVs. Order: A1 cover build + live proof first; then "live ok" + "edit ok" together, rebase
on A1's s2m_npcsync.cpp / s2n_nat.cpp, run P1-P4, implement, fight bench. hw slots 2-3 only.

All switches live cfg, default 0 during A/B on client B. No module writes CMC/anim fields every frame to fight
the game; kin_frame's RequestedVelocity is the game's own input path.

File ownership: s2m_npcsync.cpp is an npc module owned by A1, s2n_nat.cpp host list/take are outside A1's cover part
but the file is shared; edits only after "live ok" and agreement with A1/supervisor.

### 4. Live probes (after "live ok"; read-only first)

P1 client B, read-only per-frame sampler (plugin A2_slide), every copy within 30 m:
- ownership: natnpc kOn, npcsync dr owner, PMC IsActive;
- CMC: tick enabled, MovementMode/Custom +0x221/+0x222, Velocity +0xC0, Acceleration +0x318,
  RequestedVelocity +0x578, bits +0x54C, LastUpdateRequestedVelocity +0x590, MaxWalkSpeed +0x268;
- anim: PSLD anim+0xCF0 Tags (+0x10) FNames, U+0x6c8 FName, bMoving/bWalking, active montage + IsPlayingRootMotion,
  RootMotionMode;
- slip: jnt_l_foot/jnt_r_foot socket speed vs body displacement.
Slide frame = body > 60 cm/s and slip > 0.5 for > 0.3 s; log the owner and the paired host NPC velocity, mode,
montage and tags at that moment.
P2 host A, read-only per 1 s: for every human near natr, distance to the client and the host_rebuild filter result
(explains the uid 1486 drops).
P3 hw watch on B, slots 2-3 only: CMC+0x54C on a sliding copy (writers other than kin_frame); U+0x6c8 (move-tag
writer, coordinate with A1's P2); CMC+0x221 if P1 shows a non-walking mode.
P4 client B, state-changing: A/B npcsync client off vs on, natkinpin 0/1, count slide frames per 5 min; then the
fight bench.
Pass: slide frames on copies == 0 with D1 on, with no new desync in the fight bench.

---

<a id="nola-tests-a3-weapon-design"></a>

## A3 weapon design

User bug: "Some weapons is missin in npcs hands too". Client screenshot C:\Users\USER\Desktop\S2CoopDebug\bugposeCLient.png (file time 17:34): two copies with their arms raised and empty. The left one shows a muzzle flash at chest height and no gun. On the right one, a rifle hangs vertically at the right hip, away from the hands.

Offline only. No src edits, no live work, nothing written to s2rag. Status tags: PROVEN = read in code, decompile or log. NOT PROVEN = a hypothesis to test live.

### 1. Every weapon path, port status and flags

| Path | Code (S2CoopPort\src) | Ported | Release default |
|---|---|---|---|
| Host sends eq, combat bit 2 (bHasWeaponInHands), weapon mesh/class (wMesh/wCls -> look) | s2n_nat.cpp ~1711-1739 (host scan), s2x_nat.cpp host_out own_tag "NN" | yes | natnpc=1 (flags_x0), natcb=1 |
| Look weapon pairing b191h: copy gets the host gun through Obj::SetHandItemSkeletalMesh(mesh, AnimBP) | s2n_nat.cpp ~1491-1506 | yes | natlook=1, natgen=1 |
| 2 s redraw: ChangeMainHandWeapon(host eq) only when GetMainHandEquipType != host eq | s2n_nat.cpp combat_tick ~3571-3585 | yes | natcb=1, natwpnguard=1 |
| nathol: detour on FUN_140d3111a (AI holster tick) = no-op for our copies | s2n_nat.cpp ho_detour ~3073, wpn_install ~3146 | yes, log "holster tick detour on" | nathol=1 |
| natthrsrc: detour on FUN_14043628c, keeps the forced threat cache | th_detour ~3037 | yes, log "on" | 1 |
| montnull / natnoatk | mp_detour / ma_detour ~2357-2387 | yes, log "on" | 1 / 1 |
| Montage mirror stop (natmstop / natmgate) | combat_tick ~3614-3647 | yes | natmstop=1, natmgate=1 |
| pwsnap re-snap of the gun on GripPointTPP | s2m_bodies.cpp:1349 | yes, but AVATAR PUPPET ONLY (P.wcomps). Not for natnpc copies, same as in Lua | pwsnap=1 |
| offanim/offvb render relevance | s2m_npc.cpp:1568 | yes, HOST ONLY (`x0::is_host()`), same as Lua | 1 |

- Flags PROVEN equal: live A/B flags.txt (C:\s2coop_inst\A|B) against the release defaults (flags_s2core + main + main_extra + x0 + role TSV). The only differences are devcmd, luacmd, pupmvlog and the dlgend*/dmirpick* debug keys. No weapon key differs.
- The s2n_nat C defaults are PROVEN equal to the last Lua-era DLL source (offline\b191mont\cpp\src 0bbf8dda). The only differences are natcover (0 -> 1, A1's area) and aggrop (0 -> 1). In the Lua era, Lua set only natcb from a flag, so there was no hidden Lua-set weapon knob.
- Conclusion: no missing port and no flag-default difference explains the bug. It is a design gap that already existed before the port (compare the old §166 "weapon not showing but muzzle flash").

### 2. Evidence (client log C:\S2DevRoot\...\ue4ss\UE4SS.log, 17:25-17:47)
- PROVEN: from 17:30:21 to 17:32:12 the combat samples show `eq_igual` = 100 % but `arma_na_mao` (AnimHumanWeaponData.bHasWeaponInHands, anim+WeaponData+0) only 57-90 %. Examples: 17:31:22 am=93 arma=57 eq=93; 17:30:42 am=133 arma=114 eq=133. So copies kept the host equip type (rifle) while their AnimBP said "no weapon in hands", and the 2 s redraw did not run, because it only checks eq. After 17:32:23, arma = eq.
- PROVEN: in the whole session montnull nulos=0 and troca_sem_anim=0. No NULL weapon-anim montage was played and no redraw happened without an anim instance. nathol pulados was 0-877 per 10 s, so the copies' AI keeps entering holster state 2 and the detour blocks it. b191h arma_par (SetHandItemSkeletalMesh swaps) was 1-2 per 10 s while new copies were taken.
- NOT PROVEN: whether the screenshot copies were in the 17:30-17:32 window (only the file time 17:34 is known). The samples cover only copies whose host is in combat. The gun's visibility is never sampled: since b170 the look diff counts no weapon visibility.

### 3. Decompile facts (PROVEN, read in this task; not yet in s2rag, NOT verified live)
- ItemAppearanceComponent (Obj+0x7C8): +0xD0 WeaponMeshInHands (what GetWeaponInHandsMeshComponent 0x32b676 returns), +0xD8 WeaponMeshUnequipped, +0xE8 ShootingAttachMesh.
- FUN_140efe9ee is the hand-item builder. Callers include Obj::SetHandItemSkeletalMesh and Obj::vf_429.
  - For a non-local-player owner ([owner+0x650]+0x10 != DAT_149eec140), a NEW in-hands SkeletalMeshComponent is created HIDDEN: FUN_1406dbb0c(comp,0,1) = SetVisibility(false) and SetHiddenInGame(comp,1,1). It is attached to the owner Mesh at the socket *param_5.
  - The add path does NOT call vf_387, so WeaponData is not re-initialised by it.
  - With mesh==0 (remove), a non-player NPC keeps the comp at +0xD8 and calls FUN_1468603a4, which places it on the body using the look picks [[agent+0x650]+0x690]. Then vt+0xc18 is called with reason 5.
- Bit layout:
  - FUN_1406dbb0c = SceneComponent SetVisibility; bVisible = comp+0x190 bit 0x20.
  - SceneComponent::SetHiddenInGame 0x8dca04; bHiddenInGame = comp+0x191 bit 0x08.
- Agent::vf_387(r) (0xf5f8e0): for r in {1,2,5,6,7} it calls FUN_140f5f922(updater+0x440), updater = agent+0xac8.
  - FUN_140f5f922 sets WeaponData.WeaponMesh (anim+0x490) = the in-hands comp.
  - If FUN_14032b582 (the weapon mesh AnimInstanceBase) is NULL, it writes bHasWeaponInHands (anim+0x480) = 0 and stops.
  - Otherwise it async-loads the anim collection. Its delegate (vtable 0x148e9c3b0, slot +0x60 = FUN_140f5fe98) calls FUN_140f5ffa6, which recomputes bHasWeaponInHands.
- FUN_14123e904 is the draw/equip anim action (param_1[0x15] = AnimInstanceHuman). Its weapon steps run only if bHasWeaponInHands=1 and a body draw montage exists:
  - it plays the weapon montage;
  - it HIDES WeaponData.WeaponMesh;
  - it binds the delegate vtable 0x148e99b90, slot +0x60 = FUN_140f340b4 -> FUN_140f340c8 (SHOW: SetVisibility(1, propagate) + SetHiddenInGame(0, propagate) on anim+0x490, then the owner vf+0xd18);
  - then it plays the body montage (FUN_14060ee02).
  - If bHasWeaponInHands=0 or there is no body draw montage, the action just finishes and does NOT show the mesh.
- So the only show path found for an NPC's in-hands gun is FUN_140f340c8, run by a delegate of the draw action. When that delegate fires (montage notify, end, interrupt) is NOT PROVEN.

### 4. Candidate roots (NOT PROVEN, to test live)
- R1 hidden gun: the copy's in-hands mesh is built hidden (FUN_140efe9ee). The show delegate (FUN_140f340c8) never runs because:
  - (a) bHasWeaponInHands was 0 at draw time, so the action ended without a show; or
  - (b) our montage mirror stopped the body draw montage before the delegate fired (natmstop stops any copy montage the host does not play 2.5 s after OUR last eq change, but draws started by the game or the copy's AI are not covered by e.eqChg); or
  - (c) the b191h SetHandItemSkeletalMesh swap made a new hidden comp with no draw action and no vf_387, so WeaponData.WeaponMesh is stale and the gun stays hidden.
  - This fits the left copy: shots and muzzle FX come from a mesh that exists but is hidden.
- R2 bHasWeaponInHands=0 with eq equal (proven in the log above): the AnimBP weapon layer is off, giving the raised, empty-hand aim pose. The writer is FUN_140f5f922 or FUN_140f5ffa6 at a moment when the weapon AnimInstanceBase is NULL. Nothing re-inits later, because natthrsrc removed the threat flips and the redraw checks only eq.
- R3 loose rifle: either (a) the +0xD8 WeaponMeshUnequipped placed on the body by FUN_1468603a4 after a holster or remove, or (b) the in-hands mesh on GripPointTPP not following the hand bones (finding anim_weapon_attach_budgeted_mesh_child_transform; pwsnap covers only the puppet).

### 5. Live probe plan (read-only first; hw slots as the supervisor assigns)
- P1 paired dump, one host fighter and its copy (pair via s2n_nat_dump). On both sides read:
  - IAC = [a+0x7C8]: +0xD0, +0xD8, +0xE8, each with its name, AttachParent and AttachSocketName, +0x190 bit 0x20, +0x191 bit 0x08, SkeletalMesh, AnimScriptInstance and its class;
  - Mesh.AnimScriptInstance+0x480 (bHasWeaponInHands), +0x490 (WeaponMesh) == IAC+0xD0?;
  - GetMainHandEquipType, IsChangingWeapon;
  - the current body and weapon montage;
  - world distance from the in-hands comp to the hand_r bone and to the GripPointTPP socket;
  - screenshot pair.
- P2 count per copy, across a fight, on the copy only:
  - calls to FUN_140efe9ee (0xefe9ee) and FUN_140f340c8 (0xf340c8), FUN_14123e904 (0x123e904) and FUN_140f5f922 (0xf5f922), each with the return address;
  - Montage_Stop from our DLL on a draw montage (mont_stop caller = natmstop/natmgate).
- P3 hw write watch on a copy with a hidden gun:
  - on the in-hands comp +0x191 (1 byte) and +0x190 -> the last writer rip;
  - on anim+0x480 (1 byte) -> writer rip (expected 0xf5f9fa or FUN_140f5ffa6);
  - on IAC+0xD0 / +0xD8 (8 bytes) -> who swaps or holsters.
- P4 (state change on B only, after "live ok"): set natmstop 0 and look again (tests R1b). Look with natlook 0 for new copies (tests R1c).
- Root-fix direction once proven: keep the game's own draw action intact on our copies (do not stop draw montages; route the host weapon through ChangeMainHandWeapon/equip instead of a bare SetHandItemSkeletalMesh swap), so the native show delegate and vf_387 run. No per-frame re-equip, no redraw timers.

### Files
- Scratch scripts: C:\Users\USER\AppData\Local\Temp\claude\C--Users-USER\377b20f2-cf5e-4ecd-9724-1dbc2995ff02\scratchpad (fdiff.py = flag diff, vt.py / xref.py / lea.py = exe vtable reads).
- OFFLINE_REPORT §2xx was NOT appended (stopped by the coordinator).

---

<a id="nola-tests-l1-resume"></a>

## L1 RESUME

### Installed now
- Both sides (Mods and ModsClient): S2CoopNative main.dll md5 8DE41D0F8B443AC153B3C33257E14E61 (backups main.dll.bak_914f76a3).
- mods.txt: S2CoopAlife 0, S2CoopNative 1 (backups mods.txt.bak_l1).
- C:\s2coop_inst\A|B\flags.txt: cpp_net=1, devcmd=1 (backups flags.txt.bak_l1). Client dmgin is back to 1.
- The pair was handed to A1 at 17:20.
- cppbuild\Output is back on S2X_RELEASE=OFF.

### Done
- See OFFLINE_REPORT §238. Everything below passed:
  - P2, join, damage x4, fightbench 13/13;
  - time sync (after the fix), PMC Deactivate, s2q, wshot.
- Fixes: bridge nonce (s2x_bridge.cpp), @time owner (s2m_session_x0.cpp).
- Cover evidence: tests\L1_cover_evidence.md.
- s2rag: tooling_s2dev_console_exec_and_aim_calls.md and engine_crash_fun_1401acfe8_alifepopulation_stack.md are new; anim_npc_cover_crouch_pose_inputs.md is updated.

### Left: S2X_RELEASE=ON one-game smoke
1. Release DLL (md5 7D50091E7C560D3E530EBE0151C74C3C): C:\Users\USER\AppData\Local\Temp\claude\C--Users-USER\377b20f2-cf5e-4ecd-9724-1dbc2995ff02\scratchpad\S2CoopNative_rel.dll
2. Copy it over ModWork\s2coop\Mods\S2CoopNative\dlls\main.dll. Launch the host only: l1_launch.ps1 -Pair 1 -NoClient.
3. Check the log: x0 ready role=host; role defaults loaded (flags_role_host); no devcmd poll; no s2x_data reads; stable in world.
4. Put the dev DLL back afterwards: copy D:\modding\cpp\S2CoopPort\cppbuild\Output\S2CoopNative\Game__Shipping__Win64\S2CoopNative.dll (dev, same source as 8DE41D0F).

---

<a id="nola-tests-l1-cover-evidence"></a>

## L1 cover evidence

This is evidence only. A1 owns the fix.

Setup: GeneralNPC_Bandit_Stormtrooper NPCs were spawned on host A, 15-25 m from both players. Each NPC's active montage was read with S2Dev on the host NPC (port 27061) and on its client copy (port 27060), via Mesh -> GetAnimInstance -> GetCurrentActiveMontage. NPC pairs are matched by position.

### 1. Host NPCs (host side)
The host NPCs do use cover. Between 17:08:02 and 17:08:33 three host bandits played:
- MG_tp_ar_cov_hi_r_bend_in and MG_tp_ar_cov_hi_r_bend_out (high cover, peek right);
- MG_tp_ar_cover_high;
- MG_tp_ar_cov_lo_r_bend_up_in and MG_tp_ar_cov_lo_r_bend_up_out (low cover, pop up);
- MG_tp_ar_cover_low;
- MG_tp_ak74_cov_lo_reload;
- MG_tp_ar_combat_hi_idle, MG_tp_ar_combat_ak74_shoot and MG_tp_ar_combat_ak74_reload.

bIsCrouched (Character) was always false on the host NPCs. S2 NPCs crouch through the cover montages and the AnimBP, not through Character crouch. A fix that relays bIsCrouched would have no effect.

### 2. Client copies (natnpc)
The cover montages DO reach the copies. These are the same NPCs, sampled about 4 s apart:

| time | host NPC (host id) | host montage | copy (client id) | copy montage |
|---|---|---|---|---|
| 17:16:23 / :28 | 2147479315 @416832,530576 | combat_hi_idle | 2147479920 (same position) | cov_hi_r_bend_in |
| 17:16:32 / :37 | 2147479315 | cover_high | 2147479920 | cover_high |
| 17:16:41 / :45 | 2147479315 | cov_hi_r_bend_in | 2147479920 | cov_hi_r_bend_out |
| 17:16:49 / :54 | 2147459297 @415772,526977 | cover_low | 2147467280 | combat_ak74_shoot |
| 17:16:58 / 17:17:02 | 2147459297 | cov_lo_reload | 2147467280 | cov_lo_r_bend_up_in |
| 17:17:14 / :18 | 2147459277 @418369,527097 | cover_high | 2147467258 | none |
| 17:17:14 / :18 | 2147459297 | cover_low | 2147467280 | none |
| 17:17:22 / :27 | 2147459277 | cover_high | 2147467258 | none |

Same-moment pair: host 2147459297 vs copy 2147467280, read within 1 s of each other:

| time | host | copy |
|---|---|---|
| 17:17:48 | none | combat_ak74_shoot |
| 17:17:53 | cover_low | cover_low |
| 17:17:58 | combat_hi_idle | none |
| 17:18:03 | cover_low | cover_low |

The copy side's 10 s natnpc line (17:18) reads: montagens tocadas=68 falhou=0 sem_asset=0 paradas=40 tiros_anim=102; copia_inCombat=133/133.

### Reading
- Host: all the cover poses play (cover high and low, bend in/out, peek, reload in cover, cover fire).
- Copies: the same montage names play with 0 failures. Often, though, the copy shows "none" while the host is still holding cover_high or cover_low (17:17:14 and 17:17:22, two NPCs). The copy montage gets stopped early ("paradas=40" of 68 played) or never restarted. A held cover pose then drops to the standing combat idle on the client. That fits "crouch/cover broken": the copy stands up while the host NPC is still in cover.
- In each pair, the host sample comes about 4 s before the copy sample, except the same-moment table. A strict proof needs one read of both sides in the same frame. Next probe for A1: log the copy-side Montage_Stop or blend-out reason for MG_*cover_* montages.

### Screenshots
D:\modding\cpp\S2CoopPort\tests\L1_cover\cp_0..3_AB.png show A on the left and B on the right, both aimed at the 2147459297 / 2147467280 pair. It was night after the time sync, and the NPC sat about 16 m away behind cover, so the shots show little. The montage reads above are the real evidence.

### Unrelated, seen in the same session
The client crashed at 17:08:43. The access violation is inside the game (exe+0x1ad037, FUN_1401acfe8+0x4f) with ALifePopulationManager::vf_102 in the stack and no mod frame. It is the same stack as D:\modding\offline\b192door\dump2339.

---

<a id="nola-tests-npcsync-plan"></a>

## NPCSYNC PLAN

Build under test: S2CoopPort DLL md5 6d2395a1fe0bd7aaf658b7e14c22c905 (host A port 27061, client B port 27060), pair 1.
Logs: client C:\S2DevRoot\Stalker2\Binaries\Win64\ue4ss\UE4SS.log, host C:\S2DevRootHost\...\UE4SS.log, 19:01-19:22.
Probes: D:\modding\offline\a1cover\probes (pairs.js, covts.js, stuck.js, audit.js) and their .txt outputs.
Rule: "unknown" / "not verified" where nothing was measured.

### 1. Who drives a client body today

| System | File | Bodies | How it drives | Release |
|---|---|---|---|---|
| natnpc | s2n_nat.cpp | nearest natmax=8 host humans (BP_AI_Human_C) within natr=6000 of the client, host_rebuild 1590-1644, no hysteresis | adopt the matching local body (how 4, AI on) or spawn (how 2); natkin kin_frame per-frame placement + CMC RequestedVelocity; drive() MoveTo/face; natcover cover block + mode 6/4 | host stops listing for natlost=3 s -> release(): how 4 hands the body back to its local AI, how 2 XDestroyModel |
| npcsync | s2m_npcsync.cpp | host sends every live NPC within npsr=15000 of either player (npsmax 16); client pairs by uid/proto | np_take 833-904: brain StopLogic, path off, CMC tick off, Montage_Stop, PMC mover | np_rel 666-711, RestartLogic; skips natnpc bodies only on its 1 s np_pair pass (listed_addr 730-736) |
| mirrors | s2m_npc.cpp | everything not natnpc-listed and not npcsync-paired (smirrors=1, smaxnpcs 8): mutants, spill-over humans | PoseableMesh copy of the host pose | MIRROR - on death/leave |
| hidnpc | s2m_pop | client-local NPCs the host does not drive that are in threat | XKillNpcByUID | - |

### 2. Behaviour table

| Behaviour | State | Evidence |
|---|---|---|
| Cover / low crouch body | WORKS (fixed this session, natcover=1) | covts2.txt, on-screen pair 0x1966a251a80/0x1c517145a40, 20 s at 30 ms: inC 99%, action 94%, mode 99%, SmartCoverType 99%, SCP 98%; earlier pair SCP 99%, SCT 100%. Before: SCT 0/5 (before_all.txt, L1_cover_evidence.md). Screenshots D:\modding\offline\a1cover\p6_pairs.png, p7_pairs.png (same NPC low cover, host left / client right) |
| Cover mode stuck at 2 | RARE, root unknown | 1 event in ~14 min of watching all client humans (stuck1.txt 19:09:16, copy 2147477358, cb+0x910=1 and mm=2 for 21 s); 0 events in the next 10 min (stuck2.txt) with hooks on PoseSearch CMC vf_195 (exe+0xdafc66) and base vf_195 (exe+0xdb023a) and a hw write watch on the CMC MovementMode: every write in that window came from our execSetMovementMode. During the stuck window the override saw no call for that CMC; the base hook and the hw watch were not armed on it then, so a non-virtual call or a direct write is not excluded. Parked (minor), re-arm both if it shows again |
| Off-screen copy pose | BY DESIGN | PoseSearch updater runs only while the mesh is rendered (anim+0xe01 watch: 0 hits in 5 s off screen, 124 hits in 3 s on screen); off-screen SCT/SCP and bones stale. Not visible to the player, no fix |
| Locomotion legs under natkin | WORKS | fightbench a1audit1 13/13 PASS, speed ratio 0.87-0.95; client line "vel copia/host=0.98 (n=231)", erro_med 5 cm, teleports 0 |
| Sliding | BROKEN (ownership) | A2_slide_design.md R1: while npcsync owns a human, CMC tick is off and the PMC mover slides it. Live now: client npcsync "pares=2 dirigidos=1" with host natnpc na_lista=7 and host npcsync enviados 6 -> both systems hold human bodies at the same time |
| Ownership churn | BROKEN | client log 19:01-19:12: natnpc ADOTADA 13, CRIADA 2, solta "o host nao manda mais" 9; npcsync tomado 6 / solto 5; MIRROR +14/-13; hidnpc kills 9. Pattern: natnpc release -> npcsync take 0.1-0.6 s later -> natnpc re-adopt ~4-5 s later -> npcsync release 0.03-1 s later (19:10:36-19:10:43, bodies 2147478549/2147478106/2147478853) |
| Duplicate / respawned copies | BROKEN (same root) | host 2147473919: natnpc release 19:03:18 -> hidnpc killed the local body 2147477160 (XKillNpcByUID 1754) -> MIRROR + -> natnpc CRIADA 19:03:22 -> release XDestroyModel 19:07:52 -> MIRROR + -> CRIADA again 19:08:38 |
| Cover montage cut | BROKEN (same root) | np_take does Montage_Stop; A2 log 17:29:45.83 take stopped MG_tp_ar_cover_high |
| Weapon in hands | PARTLY BROKEN | client b168 combat lines: arma_na_mao 72/90, 76/95, 88/90 in many 10 s windows with eq_igual equal -> host holds the weapon, copy bHasWeaponInHands=0 (A3 R2). Screenshots D:\modding\offline\bench_shots\a1audit1_Bcrop.png: arms raised, no gun. Writer not measured (A3 candidates FUN_140f5f922 / FUN_140f5ffa6) |
| Equipment equal | PARTLY | eq_igual 70-78/90-95 in windows 19:15-19:20, 90/90 later. Which slot differs: unknown |
| Look / aim layer | WORKS (counts) | olhar_igual 100% in every window; LookAtData owner state forced by natstsrc |
| Aim in cover vs host | not verified | needs a paired on-screen measurement of the aim offset in cover |
| Copy shots | WORKS | copia_tiro_proprio=0/90, natbullet replica disparados=109 projeteis=109 perdidos=0 |
| Hits / death / corpse | WORKS (counts) | "morreu no host -> copia morta (XKillNpcByUID)", mortes counted, corpos guardados=1, acertos_host=10, dano_bloqueado=44 |
| Dead host NPC vs copy | MISMATCH seen once | audit1.txt: host 2147474536 lying (head -44, sp 0) while its copy reports sp=115 (copy off screen, pose stale); not verified on screen |
| Mutants | WORKS via mirrors | MIRROR +BP_AI_Blinddog_C_* lines; natnpc cannot take mutants (LookAtData 0x20, PORT_LOG M3) |
| PMC release Deactivate | DONE | s2m_bodies.cpp 2375 (mover_release p.deact) |
| Distance / LOD | BROKEN edge | natnpc list = nearest 8 within 6000 with no hysteresis, natlost 3 s; host npcs_classe=14 -> NPCs near rank 8 or near 60 m flip in and out, which feeds the churn above |

### 3. Root causes
- R1 (proven, A2 + this audit): two client systems own human bodies. npcsync takes human bodies natnpc just released and keeps CMC off while natnpc re-adopts; it excludes natnpc only on a 1 s pass.
- R2 (proven by code + counts): the natnpc host list has no hysteresis, so humans near the rank/range edge are released and re-adopted every few seconds, and every release hands the body to its local AI (how 4) where hidnpc may kill it, then natnpc spawns a fresh copy.
- R3 (proven counts, writer unknown): copies lose bHasWeaponInHands while the host holds the weapon.
- R4 (user bug 2026-10-17, open): in cover the copy body is right but the upper body is wrong (looks to the other side, reload at an off angle). To measure on paired samples: actor yaw, control/aim rotation, AnimBP aim offset yaw/pitch and look target, cover direction/side in the cover block, LookAt owner state, active montage with slot and start time, our face/rotation writes on the copy.
- R5 (unknown): the one cover-mode-2 event.

### 4. Design: one owner per body
- D1 natnpc is the only owner of client human bodies when natnpc=1. cfg npsnat (client): npcsync never pairs a pawn of natcls while natnpc=1; mutants and other classes keep npcsync/mirrors. Release default 1 once proven.
- D2 list hysteresis on the host: an NPC already listed stays listed while within natr*nathys and while its rank is within natmax+2 (natmax still caps new entries). cfg nathys (1.0 = off, release 1.2 once proven).
- D3 weapon: measure the bHasWeaponInHands writer on a copy (hw write watch on anim+0x480 in slot 2 when arma_na_mao drops), then fix at the source per A3 (keep the game's own draw/equip path on copies). No per-frame re-equip.
- Cover stays as built (natcover=1, event-driven: set on host enter, cleared and mode restored on host leave or release; MoveTo/nudge off while in cover).
- Spill-over humans (beyond natmax / natr*nathys) go to mirrors, as today; npcsync no longer drives them.
- D4 one owner after a release (cfg natpark): when the host stops listing a human whose uid the host still sends (npcsync #NP rows, recv within 10 s), natnpc keeps the body parked (hidden, shooters off, unkillable, still in K.own) instead of handing it to the local AI; hidnpc parks a host-known human twin instead of killing it. A parked body is re-adopted in place by natnpc (no spawn); it goes back to the local AI only when the host stops sending its uid. Mutants unchanged.
- D5 upper body in cover: fix at the writer once R4 is measured.

### 5. Proof plan
- Before/after on the same session: client natnpc solta/ADOTADA/CRIADA counts, npcsync tomados/soltos/dirigidos for humans, MIRROR +/- for humans, hidnpc kills of host-listed NPCs, per 10 min.
- Duplicate bodies per host NPC = 0 (no natnpc CRIADA for a host uid whose local twin exists or was killed); kills of released or host-known bodies = 0 (hidnpc XKillNpcByUID uid cross-checked against host uids). Baseline 19:01-19:22: 1 of 12 hidnpc kills hit a released body (uid 1754) and was followed by 2 natnpc spawns of the same host NPC.
- Paired host/client screenshots of the same NPCs (cover, walking, cover reload/peek facing).
- fightbench --lines 6 PASS.
- Switches: npsnat, nathys live in s2n_nat_cfg / x0 flags; release role TSVs default 1 / 1.2 once proven.

---

<a id="nola-tests-readme"></a>

## Test suite

One command builds and runs every suite and prints one table:

    powershell -NoProfile -File tools\run_tests.ps1

It exits 0 when there is no new failure and 1 when there is at least one. A failure that is listed in
`tests\baseline.tsv` is shown as "known" and does not fail the run.

### Options

| option | meaning |
|---|---|
| `--only a,b` | run only these suites |
| `--skip a,b` | skip these suites |
| `--list` | print the manifest and exit |
| `--full` | also run the slow `full` group (`strip_full`, all strip files instead of 30) |
| `--jobs N` | parallel suites, default min(8, cores) |
| `--timeout S` | per step timeout in seconds, default 1200 |
| `--strict` | exit 2 when a baseline row no longer fails (stale row) |

Each suite log is written to `tests\.run\<suite>.log`. Suites that need an unavailable input (the offline
oracle dirs under `D:\modding\offline\s1`, the polyhook sources of a built worktree) are shown as SKIP.
The `excl` group (`net_udp`) runs alone after the parallel suites because it uses fixed UDP ports and timing.

### Files

`suites.tsv`: suite, group (`par`, `excl`, `full`), weight (longest first), needs (comma separated paths,
`{repo}` is the worktree), steps (separated by `;;`: `bat`, `exe` or `py` followed by a path under `tests\`).

`baseline.tsv`: suite, case, reason, since. `case` is a prefix of the failure text printed by the suite.
When a baselined case passes again the runner prints "FIXED (remove from baseline.tsv)".
Adding a row is only for a failure whose cause is understood and written in `reason`.

Fixtures live in the repo (`tests\net\fixtures`, `tests\wpkg\fixtures`). Nothing reads `C:\s2coop_inst`.

### Native layer suite

`natlayer` compiles `src\s2n_nat.cpp` itself into a test with the defines, includes and libs of the
`NolaNative.vcxproj` (so the worktree must be built once). `GetModuleHandleW(nullptr)` is mapped to a fake
exe image, a stub `UE4SS.dll` is generated from the imports, and the unresolved game hooks are stubbed. It checks
the config switches, the feed buffer, the owner set, and the aggro-scorer installer (`ag_install`): refuses
other bytes, patches the three sites with near jumps to the emitted stub. It never touches a game process.

### Checklist for every new feature

Every feature needs a test (or a scenario line) for each of these four cases before it is called done:

1. Peer absent: the other side never answers (no join, no packet, no file). The feature must not hang, spam
   the log, or change local play.
2. Flag off: the flag set to 0 at boot and flipped to 0 in the middle of a session. Behaviour must be exactly
   the pre-feature behaviour, and in-flight state must be released.
3. Stale file: a bridge, save, or data file left from a previous run or an older build is present at boot.
   The feature must ignore or replace it, never trust it.
4. Second client: two clients (and a client with a different pid) at the same time. State must be per client,
   frames must carry the pid, and one client leaving must not affect the other.

Add the test to the suite of the module (or a new row in `suites.tsv`), run `tools\run_tests.ps1 --only <suite>`,
and commit the golden files with the code change.

---

<a id="nola-tests-bodies-live-todo"></a>

## Live tests: bodies

Setup: lua_guard.patch applied on both sides (not applied yet), release flags (farbody=1, pupmove=2, pupanim=1, nsmooth=1, pupcmoff=1, pupfix=1, pupfeet=1, tgtgod=1, kzsafe=1, abpguard=2, pupnoai=1, offtick=60, tgtnoint=1). cpp_bodies alone breaks the Lua readers listed in PORT_LOG "M1 bodies" X0 need 5: run these with M2/M3/M4/M6 ported too, or with the X0 Lua bridge.

PORT_PLAN M1 rows:
1. Fight bench, all rows: every row that was PASS stays PASS. Rows C3 (puppet visible, moves, animates), C4 (hidden target takes hits: `NOLA target: DANO seq=`), C19.
2. fakehost 09 (gap + leash).
3. 1.4 km teleport round trips x3 (b77tp repro): `NOLA corpos: jogador local saltou ... (teleporte) -> referencias ... largadas sem tocar`, then `corpos liberados` after bodywait, a new puppet adopted, no crash.
4. Host emission with the client beside it (D10 repro): no SetAnimationMode anywhere; `abpguard: censo` lines show sem controlador=0 for our bodies.
5. Client relaunch, then the re-adopted puppet has an AnimInstanceHuman (D6): `NOLA puppet: AnimBP do jogo mantido ... humano=true`.
6. heapchk plugin (b201) on B during the bench: HITS=0.

Probes for what I could not measure offline:
7. Snap.recv clock: x0::remote().recv must be on the same clock as x0::now() (Lua: r.recv vs os.clock). If not, age > 5 hides the puppet for good: `NOLA puppet: escondido=true` that never flips back.
8. T0 transform: AddComponentByClass without a RelativeTransform param, then relative 0/0/1. Check the weapon sits in the hand (`NOLA puppet: arma remota ... existe=true`) and the far body meshes are not offset.
9. abpGuard raw read: Agent+0xAC8 / +0xAD0 on a live BP_AI_Human_C (s2dev rd) must be the two HumanAnimController pointers Lua read through the registered properties; nonzero on a healthy NPC.
10. Far body: needs s2x_spawn_actor (X0). Without it, farbody=1 hides the NPC puppet at > pupfar and shows nothing. With it: `NOLA farbody: corpo distante criado (N malhas)` at 60+ m, walk/run anim plays, back to the NPC puppet at < 50 m.
11. Clip loads: needs s2x_load_asset (X0) for clips not already in memory; else `NOLA pupanim: clipe nao carregou ...` per missing clip and the AnimBP alone drives the legs.
12. Flag text in logs: Val::str for floats (offtick, dmgmin, pupwin) must print like Lua tostring ("60", "0.5"); compare one `offtick: valores do jogo guardados` line with Lua's.
13. remoteIn shared state: a `kzsafe: remoto FORA DO MUNDO` line may now show twice (M1 copy + Lua callers). Expected, not a bug.
14. Tick placement: Lua ran bodyGate before the other tick100 work and the bodies after it; C++ runs them together on the bodies100 row. Watch for a gate open one tick earlier or later than the Lua log.

---

<a id="nola-tests-damage-live-todo"></a>

## Live tests: damage

Nothing below has run in a game. Offline coverage is in run_parity.py: 11 scenarios match Lua line for line, plus 1 C++-only golden.

### Setup
- Both clients: flags.txt deduped, `dmgin=1` on B (release flags_client.txt line 20), `lifeguard=1`, `shotdetect=1`, `cine=1`, `tgtgod=1`.
- C++ run: `cpp_io=1 cpp_bodies=1 cpp_damage=1` on both sides. Apply tests\damage\lua_guard.patch first.
- Lua run: the same, but with `cpp_damage=0`.
- Fight: `fightbench.py --spawn --lines 3 --tag rel` (spawn3), the client standing next to the host.

### The six root-cause counters, both routes
Run `natdmg=0` (route D) and `natdmg=1` (route ND, only after X0 has merged b206).
1. Effective B dmgin: the client line `NOLA dmg cadeia 10s (cliente): ... dmgin=1`, with `desligado=0`.
2. NPCs pick the target:
   - `foco_no_alvo` > 0 in `NOLA dmg cadeia 10s (host)`;
   - the native aggrop line `alvo_como_jogador` > 0.
3. The target takes hits: `eventos` > 0 on the host line (route D), or `rota_nd` > 0 (route ND). Also M1's `NOLA target: DANO` lines.
4. #D leaves the host: `enviados` and `seq_max` rise. In A out.json, x1 carries `#D:`.
5. #D reaches B:
   - `recebidos` > 0, `novos` > 0, `perdidos` ~ 0;
   - B in.json carries the same seq.
6. B applies it:
   - route D: `NOLA dmgin 10s: aplicados=N` > 0, and the cuts `cortados_pelo_teto` / `morto` / `protecao` / `caido` read sensibly;
   - route ND: `nd_aplicados` > 0, plus the b206 `NOLA b206 natdmg 10 s (cliente)` line;
   - either way, `hp_perdido` > 0 and the client hp visibly drops.
- No double count: with natdmg=1, the host line shows `enviados=0` and `rota_nd` > 0. The client shows `aplicados=0` from #D.

### Gate rows (PORT_PLAN M2, rows C6 / C7 / C19)
- The client hp drops under host-NPC fire (both routes). Report which route is simpler. Prefer it if both pass.
- The host hp drops (native).
- A client kill on an NPC counts on the host:
  - `SHOT(core) ... hp X -> 0.0`;
  - `NOLA rep: ... MORTO` when repsync=1.
- A host kill on an NPC counts on the host.
- C6: real client shots. `SHOT real:` on B, then `SHOT(core) seq=` on A with the same seq. Head and leg hits read `osso=jnt_head` / `jnt_l_leg`.
- C7: the client goes down and gets up.
  - `NOLA LIFE: CAIDO`, then `DE PE (reanimado pelo outro jogador)` when the host stands within 3 m for 3 s;
  - otherwise `DE PE (tempo)` after 20 s;
  - while down, `#L:w` reaches the host and no #D hit applies (`caido` count).
- C19: the hidden target is parked or back. During tgtPark, `relmir` and `repfoe` skip (`alvo=estacionado` on the host chain line).

### Checks with no offline cover
- X0 Call with dotted struct paths: `BriefDamageData.Damage` and `BriefDamageData.AttackerUID.UID`. A refused call logs `ok=false chamada recusada`.
- `ForceSetHP` on an int param, `SetMovementMode` on byte params, `DisableMovement` on CharacterMovement.
- `x0::own_tag("@shots")` reaches out.json `"shots"`. The host `x0::remote().shots` carries it back.
- The OnShotSoundStart hook: `GetOwner` on the queued self, and the camera ray from `PlayerCameraManager`.
- `s2rel::get/set` (relfoe=1 / relmir=1 on A): `NOLA relfoe:` and `NOLA relmir:` lines.
- Down message: X0 screen_text added by U1 (s2x_ui.cpp, S2X_HAS_SCREEN_TEXT on); live screenshot proof by U1.
- Peer relaunch: after `PEER SESSION`, a restarted seq 1 is applied again (the seen sets were cleared).

### Mixed-mode caveats
- cpp_damage=1 with cpp_travel=0: no host-cinematic gate. The Lua cv state is not visible, so #D is not cleared and shots are not dropped during a host cinematic.
- cpp_damage=1 with cpp_lock=0: s2m_lock::shot_deny is inert, so the N3 story-NPC shot deny is off.
- links().nd_dead is always empty (nodeath is DELETE, release nodeath=0), so the batch-13 dead state never stops lifeGuard. This matches the release.
- cpp_damage=1 with cpp_bodies=0: m01::dmg() is fed only by C++ M1, so no #D events are produced.

---

<a id="nola-tests-items-live-todo"></a>

## Live tests: items

| # | check | setup | pass when |
|---|-------|-------|-----------|
| 1 | C12 | release gate scenario C12 (container loot both sides) | same items on both sides, no dup, LOCK_DENY on the second opener, TAKEN kept after reload |
| 2 | C10 | release gate scenario C10 | same result as the Lua run in the gate log |
| 3 | fakehost 05 | fakehost run 05 | same NOLA LOCK_/TAKEN/LOOT log lines as the Lua baseline |
| 4 | fakehost 06 | fakehost run 06 | same as above |
| 5 | corpse loot, host side | host kills an NPC, loots the cloot body | body loot opens, items arrive, client copy updated (#CL), no second body |
| 6 | corpse loot, client side | client loots a host-killed NPC | LOOT_GOT / cloot copy correct, the host window closes for a given body |
| 7 | ptake 0.5 s (b189) | take part of a box on one side, open it on the other within 0.5 s | "ptake: aplicado na minha copia" on the other side, no item twice |
| 8 | 215 m teleport then loot (b192) | teleport the client 215 m, loot a corpse right after | no crash; status "items" shows the inv guard count instead of a read of [actor+0x650] |
| 9 | M3 gap | host corpse with cpp_items=1 before M3 provides npcUid | #CL uid 0 on host: confirm client skips clcopy (known gap until M3 npcUid) |
| 10 | catch-up | cpp_items=1, cpp_save=1, cpp_quest=1, client rejoins | "NOLA quest: catch-up aplicado" line matches the Lua text and counts |

---

<a id="nola-tests-lock-live-todo"></a>

## Live tests: lock

Pair 1: host A and client B, flags lead=1 ldblk=1 choice=1 dmir=0 vendtrade=0 (release set), A or B on C++ (wire is unchanged: tag #LK, same log text).

1. C9 / b109: A opens a story dialog (any non-vendor NPC with quest lines). Log on A: `NOLA lead: trava #N tomada (dlg em x,y,z)`; out.json carries `#LK:h,...,dlg,...`. B walks to the same NPC: B log `NOLA lead: NPCs de historia sem interacao aqui (total n): o outro lado lidera`, the NPC prompt is off on B (no F prompt), no dialog opens.
2. b127: A closes the dialog. B log `NOLA lead: NPCs de historia liberados (o outro lado soltou a trava)`, prompt back within 1-2 s. A dialog lock left open must also end by itself after ldwatchs (600 s): log `watchdog b127`.
3. Held fallback: B opens a dialog in the same second A does (lock event not yet arrived). B log `dialogo aberto com o outro lado liderando (dlg #N): SEGURADO (respostas escondidas)` then `respostas escondidas`, answers hidden, `dialogo segurado fechado (UIDialogClose) ok=true` after ldclose (4 s). When A releases first: `respostas devolvidas (o outro lado soltou a trava)` and B takes the lock.
4. Tie: both open at once. Client log `empate: os dois tomaram a trava ... o HOST vence, o cliente segue`.
5. Vendor free: B talks to a trader (Rostok bartender, or the Zalissya trader) while A holds a lock. B log `dialogo com vendedor: livre, sem trava (vendtrade/ldblk)`, normal dialog and trade work, no NPC of a vendor within vendtr 1500 cm is blocked.
6. Trigger lock: A walks into a branch trigger (s2u_choice trig tier 1). Log `trava #N tomada (trig ...)` and the lock ends by itself after ldtrig 3 s (`solta: tempo`).
7. N3 choice: B shoots a branch NPC while A leads: A log `tiro em NPC de historia <guid> do cliente NAO aplicado`. B shoots with no lock: `tiro do cliente ... aplicado: o cliente lidera 3 s`. B pulls a lever from the use table: A log `uso ... do cliente NAO aplicado`; B prompts of branch usables near B are off (`NOLA choice: ... bloqueado no cliente`).
8. ldsave: after load, `NOLA ldsave: pawn #1 +8 s: ...` and `+33 s` lines, registro N/U counts; ledger file bridge\s2_blk_ledger.txt written.
9. No widget walks: heapchk plugin and the dm70 crash class (access violation 0x18 around W_DialogueView_C) must stay silent for a 30 min session; the module only reads IsInViewport / IsVisible, AnswerContainer GetVisibility / SetVisibility (collapsed = 1), UIDialogClose, UIDialogOpenTrade / UIDialogOpenUpgrade, ButtonHintTrade GetVisibility.
10. Fight bench with cpp_lock=1 on both: every row that was PASS stays PASS.

Needs X0 before row 7 can pass: Call::raw (see PORT_LOG, M8 integrate block). Without it the host cannot resolve a branch NPC from its placeholder guid, so shots are never denied (the C++ build compiles without S2X_CALL_RAW and returns no actor).

Unmeasured by me (offline): CppMediator GetGUID / GetActorByGuid param names (Actor, TargetGUID) come from the object dump; whole ProdWorld (x0::Call / prop reads on BP_AI_Human_C, InteractableObject, InteractionComponent, BedView, W_DialogueView_C) has only been compiled, never run.

---

<a id="nola-tests-m11-live-todo"></a>

## Live tests: m11

Prereq: X0 integrated, s2m_session_x0.cpp added to the build, lua_guard.patch applied by the supervisor.

C-rows
- C11 emission follow: fakehost scenario 04_emission_follow.txt. Expect the same log lines as the Lua run: "agenda propria de emissoes em pausa", "host em emissao", a real client emission from the host weather 7, NO XStartEmission, "parada 1 de 3" at most once, saves allowed after.
- C14 time and weather: client with synctime=1 syncweather=1 wxfollow=1: "TIME: XSetGameTime(...) sync gt" when the clocks differ over 600 s, "clima: host em N" + "troca para N confirmada".
- C20 version check: hostcfg=1 on both: "PEER SESSION", "hostcfg: s2core.lua igual nos dois lados", flag adoption lines (difficulty).
- Sleep (N5): host sleeps, client follows (mode 1) or refuses in a dialog; beds blocked while the other is busy; "DORMIMOS JUNTOS".
- No pause (N8): Esc menu on both, "nopause: jogo pausado -> despausado" and the menu usable.

Unmeasured, probe with s2dev (read only)
- x0::prop<uint8_t> on the EnumProperty CurrentWeatherData.TargetWeather (byte at +1 of the struct).
- x0::Call::i on EnumProperty params (XSwitchToWeather/XForceWeather WeatherType) and ByteProperty NewType (SetCollisionEnabled).
- x0::prop<Ref> for BedView.BedMeshComponent.
- Call::rb for GetCollisionEnabled returns a byte: read with ri.
- ftLock / nodeathDead / cineFrozen need M10/M2 interface slots (adapter returns false / story_locked for now): sleep busy states B and X are only partly covered until those exist.
- sleeppull (default 0) needs the M10 pull-now call; the adapter returns false.
- build_md5 / main_ver / core_ver are read as flags by the adapter placeholders; X0 should provide the real values (DLL md5, mod and core version strings).
- Fight bench is not affected by this module (no combat code); run it once after integration to confirm no regression.

---

<a id="nola-tests-m5-live-todo"></a>

## Live tests: m5

Offline state: 26 Lua-vs-C++ parity scenarios identical, 6 C++-only fast-mode scenarios pass, TSV round trip 1278/1278 rows, 39 flag defaults checked (run tests\m5\run_all.bat). The ProdWorld adapter (src\s2m_world_x0.cpp) only compiles; every UE call in it is unverified.

### Adapter calls whose names are guesses (verify with one log line each)
- NiagaraFunctionLibrary.SpawnSystemAtLocation param names: WorldContextObject, SystemTemplate, Location, Rotation, Scale, bAutoDestroy, bAutoActivate, PoolingMethod, bPreCullCheck.
- AkGameplayStatics.PostEventAtLocation param names: AkEvent, Location, Orientation, WorldContextObject.
- SetStaticMesh param NewMesh, SetSimulatePhysics bSimulate, SetActorHiddenInGame bNewHidden, SetActorEnableCollision bNewActorEnableCollision, SetEnabled bInEnabled, SetBroken bInBroken, PauseSkeletalComponent bPause, SetInteractionActive bActive. The Lua calls pass them positionally; X0 Call is by name.
- The BndEvt__... delegate functions are called with zero args from the s2u_actions table (Lua does the same); confirm X0 Call::run with no params invokes them.
- DoorState write: the adapter tries int32, uint8 and float on the anim instance; the real type is not verified.
- K2_GetComponentRotation is read as (pitch, yaw, roll) through Call::rr; order not verified.

### Behaviour to check on a real run
- NullMesh: when the StaticMeshComponent.StaticMesh read fails or is null the adapter reports NullMesh (meshsafe, b77tp). Confirm no crash on a streamed-out prop.
- asset(): find_path only. Lua falls back to LoadAsset when the mesh is not loaded; X0 has no such call, so a destroyed prop whose replacement mesh is not in memory skips the mesh step ("malha ok=false").
- gate: key is addr|fullname of BP_Stalker2Character_C, open = iface().body_gate or true. Confirm doors/dobj stay quiet while the remote body is out of the world.
- is_a in the adapter ignores the Lua depth limit; check an InteractableObject subclass deeper than the Lua limit is accepted on purpose.
- Table-load logs name the .tsv files (Lua names .lua); ientab step failures print "!erro" (Lua prints the Lua error text).

### Fast detection (the point of this port)
- The 1.2 to 1.8 s host-side delay (OFFLINE_REPORT section 213) is NOT explained: section 203 measured 2.7 to 3.0 s of 3.1 s as the 3 scans x 1 s poll, section 213 never split the A->B time. The C++ removes the poll cadence (about 0.15 s), the 3-miss debounce (1 miss plus the DG.alive check) and requests an immediate out flush. Measure on a live break: the report line now reads "sumiu N varreduras T s, ultimo visto ha X s" and gives the detection time; compare it with the time the other side applies it.
- Cost: the poll validates tracked Refs only (no actor list). Measure ms per frame row and ms per 1 s full scan on the fight bench with dobjfast=1 versus dobjfast=0.
- A bottle on a shelf destroyed by a thrown object, a plank pushed (physics nudge), a crate shot: each must show one #Z entry on the other PC within about 0.3 s. Run one of each.
- Re-streamed copies (walk away 150 m and back after a break) must stay hidden on the receiver and must not be re-reported by the breaker.
- dobjfmiss=2 and dobjfast=0 are the rollback switches; confirm dobjfast=0 behaves like the Lua (3 scans of 1 s).

### X0 gaps this module depends on (see PORT_LOG, M5 block)
- flush_out: an immediate out.json flush after a report. Without it the report waits for the normal out cadence; env_.flush_out() is an empty default, so detection works but the second hop is not shortened.
- Flag defaults for dobjfast (1), dobjfsec (0.15), dobjfmiss (1) in flags_x0.tsv, and HC_KEYS membership if hostcfg should carry them.
- cpp_world is the switch name in s2x_sched.cpp (the brief said cpp_m5).

---

<a id="nola-tests-net-live-todo"></a>

## Live tests: net

Offline results: tests\net\parity.py and tests\net\udp_test.py (both PASS, see OFFLINE_REPORT "Port R1 relay"). Everything below needs the real game or two PCs.

1. Two PCs over Radmin VPN, both cpp_net=1 netfiles=1 netpeer=<other VPN IP>. The ports come from the role: host listens on 7779 and sends to 7778, client the reverse. Check:
   - each log has `relay v2 listen=...` once;
   - `relay stats 10s` has recv>0 and bad_peer=0 on both sides;
   - the avatar moves;
   - fight bench rows A1-A6 pass.
2. Mixed pair, as in the field: one PC runs the DLL (cpp_net=1), the other runs relay_v2.py (cpp_net=0). Run it both ways. It must play the same as row 1.
3. Firewall, first run on a PC with no "S2Coop relay" rule:
   - does Windows show a "Windows Security Alert" for Stalker2-Win64-Shipping.exe when the DLL binds 0.0.0.0?
   - after "Allow" (Private), does the peer get datagrams?
   - repeat with only the port rule from install.ps1 (`netsh ... localport=7779`, no program). Does that rule alone suppress the prompt and let traffic in? Not verified offline.
   - repeat with the program-scoped rule proposed for the installer.
   - the LAN case: the "Rede 2" network is Public on this PC. Check a Private-only rule there.
4. Port conflict: start relay_v2.py on the same port while cpp_net=1. Expect `RELAY ERROR: bind UDP ... (WSA 10048)` every 5 s. Stop relay.py: expect `relay: UDP ... bound after N failed tries` within 5 s, then sync resumes. Also toggle cpp_net 0<->1 in flags.txt with the game running; expect one S2NET line per change, and the port freed when off.
5. PEER SILENT: quit the peer game or its relay. Expect `NOLA PEER SILENT` after peersilent s on the other side (driven by in.json "t", unchanged path). Restart the peer: expect PEER up, and NPC copies cleared on the sid change.
6. sxjoin join with the DLL relay on both sides, then mixed (DLL host + Python client, and the reverse):
   - sx_req.txt / sx_out.pkg / sx_in.pkg flow;
   - `relay sx` lines;
   - a save of the real size (offline used 300 KB with 20% loss);
   - resume after killing the client game halfway (sx_in.map / sx_in.part kept).
7. fakehost --net against the DLL: fakehost.py sends HDR+APP only and reads HDRs. Profiles internet-good / internet / internet-bad against a game with cpp_net=1.
8. Latency and cadence in game. Offline file mode, out.json written to in.json visible on localhost: median 27-35 ms, p95 42-55 ms, same as relay_v2.py. Measure in game with the shots/ping rows of the fight bench. Check the game frame time does not change with cpp_net=1: the net thread does zlib + JSON for 21 KB headers at 10 Hz, about 1 ms per frame on this PC.
9. Mailbox mode (netfiles=0) needs the X0 bridge seam first (PORT_LOG "R1 net"). Then repeat rows 1, 5 and 6 with netfiles=0.
10. Hot reload / uninstall (s2dev plugin reload): x0_stop must run from ~S2CoopNative. Expect no crash on reload, and the port free for the reloaded DLL.

---

<a id="nola-tests-pop-live-todo"></a>

## Live tests: pop

Pair 1, client B with alifeoff=1, host A Lua or C++ (wire is unchanged).

1. AI feature call: XDeactivateAIFeature takes an EnumProperty `Feature`. Lua wrote 203647 into it. x0::Call.i refuses a size mismatch, so this is the first thing to read: log `NOLA alife: DESLIGADO ... ok=true,true` must appear; `chamadas falharam (ok=false,...)` means the enum width differs (probe: s2dev props on CustomConsoleManagerAM XDeactivateAIFeature, then pass the right width).
2. C5: B census. After DESLIGADO count hidden live non-own pawns (S2Dev find BP_AI_Human_C, bHidden) vs the host list (A out.json npcs); hubs and trade places stay visible and usable (talk to a trader in Rostok, F key).
3. C5: hidnpc. Spawn a dog pack near B (spawn3.lua on A is host only; on B use a hidden dog seen in threat) and read `NOLA hidnpc: NPC local escondido ... XKillNpcByUID(uid) ok=true`; second try after 5 s uses XDestroyModel; a natnpc-listed uid must log `esta na lista natnpc do host`.
4. C12: vendors local on both sides (D3 recipe), vendmir=1 vendone=1: host log `NOLA vend: NPC em x,y,z sem espelho`, client keeps the same single NPC visible; vendor talk opens trade on both.
5. D14: orphsweep=1 orphrm=3 after a client relaunch with an old S2Coop_RemoteTarget in the save: `NOLA orfao: ... -> escondido=true ...` and the adopted body untouched. Dry run first with orphsweep=2.
6. qfall: drop a quest item outdoors with the inventory open, `NOLA qfall: ... de volta em z` appears once; needs the trace helper (item below) or the log reads `pes do jogador (trace falhou)`.
7. Fight bench with cpp_pop=1 on B: every row that was PASS stays PASS; heapchk plugin on B HITS=0; natpelast empty.

Unmeasured by me (offline): worldKey is the local pawn Id (Lua used ST.wg.key); GetFocusedEnemy / GetGUID / GetPrototypeID param names come from the object dump (Obj, Actor, Actor).

---

<a id="nola-tests-quest-live-todo"></a>

## Live tests: quest

Nothing below has run in a game. Offline coverage: parity.py, 15 scenarios match the real s2core ranges (md5 0b56e1b5) line for line, file for file.

### Setup
- C++ run: `cpp_io=1 cpp_quest=1` on both sides, tests\quest\lua_guard.patch applied. X0 must register the `s2q` console handler first (PORT_LOG M7 X0 need 1), or s2q commands do nothing.
- Lua run: the same with `cpp_quest=0`. Compare the `NOLA quest`, `qitem`, `qpick`, `qdrop`, `qdiv`, `trig`, `qreward`, `rb` log lines and the x1 tags QN W J QD S B QI QP in out.json.

### Fakehost scenarios (s2coop\tools\fakehost_scenarios), C++ vs Lua equal
- 01_catchup_first_join: #S catch-up digest, client replays once, cuDone set.
- 02_live_steps_then_client_load: live #J steps, then a client load: the quest log cut and the replay after the reload.
- 07_host_rollback_client_ahead: #B host gen bump, client rbWait, loadLastSave, rb_done.
- 10_host_relaunch_older_save: campaign id / rbGen after a host relaunch, quest_log rewrite.
- 11_client_load_no_leave_save: questRollback on the client, qlOk.

### Rows
- C8 quest progress sync: one quest step on A shows on B (journal and markers); quest item given on A lands on B too (b164); a trigger walked by B fires on the host once (b98 trigself, one `QN` per seq).
- C17 desync detection: qdiv A. Let B miss one host journal step (drop its #J for one step, e.g. B paused through it), the detector logs the divergence and repairs it (qdFix) or rolls (qdRoll) as Lua does.

### Native behaviour only a game can show
- Hold-D drop: hold D over a quest item in the inventory (key_hold.ps1). The qdrop hold cycle must call OnDropItemHoldTriggered once. Compare x0::key_down with PlayerController:IsInputKeyDown(FKey D) (X0 need 3).
- qpick: lead dialog on A, B pick waits (lead_dlg / host_dlg_open from M8).
- qdiv journal read through CppMediator (qdivj): the counts match the journal UI.
- GameTimeSeconds read live (Env::game_secs) vs the main.lua cached S2_gameSecs: the qreward and qdiv timings line up.
- XCreateItemInInventoryByID reward items (qreward #W) arrive once on the receiver, no duplicate after a reload.

---

<a id="nola-tests-save-live-todo"></a>

## Live tests: save

Prerequisites: run `uv run --no-project python -I tests\save\patch_save.py --apply` (it adds the s2n_save_api_* / s2n_join_api_* exports). Add src\s2m_save.cpp and src\s2m_save_x0.cpp to CMake. Flags: cpp_save=1, cpp_quest=1, cpp_travel=1, cpp_items=1, cpp_io=1. Apply the tests\save\lua_guard.patch.

1. Boot log: "NOLA x0 module save registered (port=1)" and no "modulo parado" line.
2. Row C2 (client saves with the host, b165/b167): the host saves, then the client logs the forced autosave, n7sv_pares.txt gets a pair row, and the client's #N count goes up on the host.
3. Row C7 (host death leads to a host load): the client follows (n7 restore). The client keeps only its own items, quest rewards are kept, and it has no duplicate items.
4. Row C13 (sxjoin join / rejoin): first set sxjoin=1. Release flags_client.txt has no sxjoin line, so it defaults to 0. Then check want -> host pack -> install -> XLoadLastSave -> kit restore -> mark installed.
5. Fakehost 07 / 08 / 10 / 11. With csold=0, the 08 and 11 save-timer paths are gone (DELETE). Mark those steps obsolete. Do not count them as failures.
6. UFunction parameter names (not verified; Lua passes them by position):
   - XCreateItemInInventoryByID(PrototypeID, ObjUID, Count, Durability);
   - ModifyMoney(Delta);
   - the type GetMoney returns (read as float with rf).
   - If a name is wrong, the call fails safely: Call is bad_ and run() is false. The kit/join restore then logs an error and gives nothing.
7. +0x650 guard: with a pawn whose +0x650 is null (teleport race b192), itemCount refuses and logs "+0x650 nulo" up to 5 times. It must not crash.
8. em.noSave: s2m_session_em_nosave is an extern "C" weak symbol (fallback false) until M11 exports it. Check that the client does not save during an emission.
9. Row order: the save100 row must run after quest100 (M7 rbTick) and before travel's catchupIn. Check this in the x0 status row list.

---

<a id="nola-tests-steam-live-todo"></a>

## Live tests: steam

Nothing below was run. Offline proof: out\steam_result.txt (56 PASS) and out\glue_result.txt (fake steam_api64).

### One PC, one Steam account (only after X0 integrates; set `net=steam`, role host)
1. UE4SS.log shows these, in this order:
   - `S2NET steam: started`
   - `steam_api64.dll is loaded`
   - `hooked the game's SteamAPI_RunCallbacks`
   - `ready: user <name> (<id>), app 1643320, role host, overlay on`
   - `friends-only lobby <id> ready`
   This proves the hook reaches the real slot 0x149f0d170, and that the game's OSS pumps it.
2. If the log has `waiting for the game's first SteamAPI_RunCallbacks` but no `hooked` line, the slot is not called through. Example: the OSS dispatch never ran, or the dev exe differs. Record the two pointers it prints.
3. `steam` (s2q console) status line: state `hosting`, pumps rising, last_err 0.
4. In game, press Home. The Steam overlay invite dialog opens and lists friends. With the overlay off, the log says so.
5. The friend list shows the host as "Playing S.T.A.L.K.E.R. 2" with Join Game. This needs the second account to see it.
6. Firewall: no Windows prompt from our side, because the relay binds 127.0.0.1. Check whether steamclient's SDR socket triggers a prompt (not verified).
7. With `net=ip`, no `S2NET steam` line appears at all.
8. With Steam offline (Steam started in offline mode), the log shows `Steam user not ready within 60 s ... using the IP route instead`, then `S2NET route: ip`.

### Two PCs, two Steam accounts that are friends (the real test)
1. Host: role host, `net=steam`. Client: role client, `net=steam`. Neither has a netpeer, VPN or open port.
2. Invite path: the host presses Home and invites the friend, and the friend accepts in the overlay. The client log shows `joining lobby`, then `joined the lobby of <host>`, then `session with the lobby peer ... accepted`. The host log shows `<friend> joined the lobby: co-op link up`.
3. Join Game path: the friend uses Join Game in the friends list while the game is running. The same lines appear.
4. Cold start path: the friend's game is closed, and the friend clicks Join Game or accepts the invite. Steam starts the game. Check:
   - whether the shipping exe gets `+connect_lobby <id>`: the log should say `launched by Steam to join lobby ... (+connect_lobby)`;
   - what the launcher (Stalker2.exe) does with it. Unknown.
5. Game reaction (unknown, important): when the invite is accepted, does UE OSS / the game try to travel, show a dialog or kick to the menu? The OSS only logs "Entered lobby ..., but not found in sessions list". Watch for a map change or a popup.
6. Relay over SDR. Play 10 min in a busy area, then run `steam` and `net` status on both sides. Check:
   - send_err 0 (if not 0, note last_err, e.g. 25 LimitExceeded);
   - the recv counts follow the sent counts;
   - PEER SILENT never appears;
   - NPC copies are as smooth as on the IP route.
   The host sends 62-72 KB/s (relay.log); whether SDR keeps that rate without loss or delay is not verified.
7. The host quits. The client log says `the host left the lobby; waiting for a new invite`. When the host comes back and invites again, the client rejoins.
8. A stranger: a third account that is not the lobby peer sends to the host. The log shows `session request from ... not accepted`.
9. Fallback: on the client set `net=ip`, with a netpeer. The relay switches to UDP without a game restart (on_flag).
10. Save transfer (sx) over Steam: the client joins fresh (sxjoin=1) and the save arrives with a matching crc.

---

<a id="nola-tests-travel-live-todo"></a>

## Live tests: travel

Pair 1, host A and client B, same flags.txt as the release (leashown=1 tpfloor=1 tpfit=1 ftfollow=1 cjoin=1 cinedlg=1 mqpull=1). cpp_travel=1 on both, Lua guard applied.

1. Adapter probes, read first. s2m_travel_x0.cpp was only compiled, never run. Check in the log: no `x0 call failed` line for K2_SetActorLocation, K2_TeleportTo, SetMovementMode, DisableMovement, StopMovementImmediately, IsFalling, GetHP, ForceSetHP, GetBleeding, ForceSetBleeding, XSetEntityUnkillableByUID, LineTraceSingle. Param names assumed: NewLocation/bSweep/bTeleport, DestLocation/DestRotation, NewMovementMode/NewCustomMode, HP, Bleeding, PlayerController (DisableInput/EnableInput), EntityUID/bGodModeState, LineTraceSingle WorldContextObject/Start/End/TraceChannel/bTraceComplex/DrawDebugType/bIgnoreSelf/DrawTime and the out struct read `OutHit.ImpactPoint`.
2. Trace read. `NOLA tpfloor: ... K2_TeleportTo tentativa 1 ok` needs a floor impact; if every pull logs `atras sem trace` or `sem chao`, the OutHit.ImpactPoint read failed (s2dev props on KismetSystemLibrary LineTraceSingle, then give X0 s2m_trace_line instead).
3. Streaming source. `s2m_travel_spawn_source` has no body until X0 provides it (weak stub returns 0). Without it a far pull still works (fly mode, floor trace) but the destination is not pre-streamed: do the 1.4 km teleport round trips x3 (b77tp repro) on B with the source stubbed, then again with the real source. Both must end with `NOLA tpfloor: CHEGOU` and no crash; heapchk HITS=0.
4. C16 cutscene join (recipe 10-16 19:00): A starts a main-quest scene node, B logs `NOLA cine: cliente CONGELADO e protegido` and `NOLA cine: congelado mov=true ... god=<uid>`, then `NOLA cine: cliente LIBERADO`; A logs `NOLA cjoin: causa ... do cliente leva a ... -> host` when B fires the cause. Repeat with B starting the scene (`NOLA cjoin: antes de ..._S2C -> teleporte para juntar` on B, tpfloor pull `cjoin cena` beside A). Compare the tp_first / tp_on_path scenes with a Lua run of the same save.
5. Fakehost 03 (cine freeze): the #V sequence 0,1,0 and tseq bump on a position jump above cinejump, client frozen until `cinehold` and never longer than `cinemax` 180 s.
6. cinedlg: talk to an NPC on A, B freezes, host body not hidden; after the dialog the view stays in the viewport hidden (IsVisible false) and B must release.
7. tpfloor / tpfit pull to the partner: walk B beyond leashm (350 m) with leashown=1: `COLEIRA FORA d=...m`, then `NOLA tpfloor: ... K2_TeleportTo tentativa N ok` and `CHEGOU`, B stands beside A on the ground, never inside a wall. Also the sleep pull (M11 calls s2m_travel_pull_now).
8. C15 fast travel (probe b100): A uses a hub travel, B gets `NOLA ft: o outro jogador viajou para ...` then `seguir para ...`, lands beside A within ftwait 45 s; the other way too (B travels, A follows); both travel at once = host wins. Dialog open on the follower: hold, then follow.
9. cfollow / cfall: B falls through the floor during a pull: `NOLA cfall: cliente caindo fora do mundo` rescue lifts B 100 cm above A.
10. leashown always on: the C++ owner has no leashown=0 path. Confirm `NOLA coleira:` lines show the effective value for each park/pull (join_park, join, nodeath, ft_park, ft), and that M9 requests arrive (needs s2m_travel_lr_set from M9; until M9 is ported the Lua M9 requests are lost and the leash stays at the base value).
11. Fight bench with cpp_travel=1 on both: every row that was PASS stays PASS, heapchk plugin HITS=0, natpelast empty, rows C15 and C16 PASS.

Offline deliberate differences to watch: the dialog view is scanned once for both cine and ft (Lua kept two copies); `leashm mudou por fora` is replaced by `flags.txt leashm a -> b`; remoteIn hasYaw is always true.

<a id="nola-pr-template"></a>

## Pull request checklist

### What this changes

<!-- What was broken or missing, and what happens now. Link the issue: Fixes #123 -->

### How I tested it

- [ ] `tools\run_tests.ps1 --all` passes (or only shows SKIP for suites I can't run)
- [ ] I added or updated an offline test that fails without this change
- [ ] In game (optional): host + how many clients, Steam or LAN/IP, what I checked

### Checklist

- [ ] One fix or feature in this PR
- [ ] No game files, extracted game data, decompiled code, saves or binaries
- [ ] No personal data (IPs, Steam IDs, names, paths with my user name)
- [ ] Generated tables in `data/` regenerated if I changed their generator
- [ ] I agree my change is released under the GPL-3.0 licence

</details>

<details>
<summary>Version 1.2.0 screenshots</summary>

<a id="nola-v1-2-0-readme"></a>

## Version 1.2.0 screenshots

Screenshots of what changed in v1.2.0. Every shot shows the other player's character as the host sees it. "Before" is v1.1.2 behaviour (the fix switched off), "After" is v1.2.0. A few fixes have only an "after" shot because we have no clean capture of the old behaviour.

### Reloading with a rifle

The other player's arms now move through a real reload instead of staying frozen in the aiming pose while the rifle drifts away from the hands.

| Before | After |
|---|---|
| ![Before](v1.2.0/01_rifle-reload_before.jpg) | ![After](v1.2.0/01_rifle-reload_after.jpg) |

### Climbing ladders

The other player now climbs a ladder with hands on the rungs instead of hanging in front of it in a walking pose.

| Before | After |
|---|---|
| ![Before](v1.2.0/02_ladder_before.jpg) | ![After](v1.2.0/02_ladder_after.jpg) |

### Knife grip

The knife now sits in the closed fist with the blade pointing forward, instead of sticking out sideways and backwards.

| Before | After |
|---|---|
| ![Before](v1.2.0/03_knife-grip_before.jpg) | ![After](v1.2.0/03_knife-grip_after.jpg) |

### Detector in one hand, bolt in the other

The detector now goes in the left hand and the bolt in the right. Before, both ended up in the same hand.

| Before | After |
|---|---|
| ![Before](v1.2.0/04_detector-and-bolt_before.jpg) | ![After](v1.2.0/04_detector-and-bolt_after.jpg) |

### Holding the bolt

The other player now holds the bolt up in the right hand, as in the game's own animation. Before, the arms just hung down with nothing in them.

| Before | After |
|---|---|
| ![Before](v1.2.0/05_bolt-grip_before.jpg) | ![After](v1.2.0/05_bolt-grip_after.jpg) |

### Reloading a pistol

During a pistol reload the pistol now stays in the hand and the other hand comes up to it. Before, it floated away from the hand. The two shots are from different moments of the reload.

| Before | After |
|---|---|
| ![Before](v1.2.0/06_pistol-reload_before.jpg) | ![After](v1.2.0/06_pistol-reload_after.jpg) |

### Aiming pose and lowered weapon (H)

The other player aims with the weapon raised at the shoulder, and carries it lowered when they press H.

| Aiming | Lowered with H |
|---|---|
| ![Aiming](v1.2.0/07_aim-and-lowered-weapon_after_aim.jpg) | ![Lowered](v1.2.0/07_aim-and-lowered-weapon_after_lowered.jpg) |

### Gunshots on the other player

When your partner fires, you see the shot on their character, with muzzle smoke and flash. The game's own fire animation plays for each weapon.

| After |
|---|
| ![After](v1.2.0/08_partner-fire_after.jpg) |

### Vaulting

The other player vaults through a window with their feet up at sill height.

| After |
|---|
| ![After](v1.2.0/09_vault_after.jpg) |

### Searching a stash

While a partner has a stash open, their character crouches and searches for as long as it stays open, then stands up when it closes.

| Standing by the stash | Crouched while it is open |
|---|---|
| ![Standing](v1.2.0/10_stash-crouch_standing.jpg) | ![Crouched](v1.2.0/10_stash-crouch_after.jpg) |

### Death screen

A co-op death now shows the real cause of death (or the game's default text) instead of always "shot". This fix has no screenshot.

</details>
