/*

 **************************************************************************

 Wolfenstein Reloaded
 Developed by Morgan Jones <maclover201@me.com>
 File Description: Player rendering code

 **************************************************************************

 Copyright © 2010 Morgan Jones

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.

 **************************************************************************

 */

#include "defs.h"

#include "rObject.h"
#include "tID.h"

#include <cmath>

#ifndef WOLF_PLAYER_H
#define WOLF_PLAYER_H

/*!
 *	This class represents one player's render object in the game.
 */

class rPlayer : public tID {
public:
    rPlayer();
    void setPosition(rPoint position);
    void setAngles(float angle1, float angle2);
    void updateCamera();
private:
    rPoint _position, _view, _up;
    float _upA, _viewA;
};

class rPlayerManager : public tIDManager <rPlayer> {
public:
    static void renderAllViewports();
    static void addPlayer(rPlayer * player);
    static void removePlayer(rPlayer * player);
};

static rPlayer rDefaultPlayer;

const float deltaView = 1.0f;
const float deltaUp   = 1.0f;

#endif /* WOLF_PLAYER_H */
