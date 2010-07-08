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

#include "rPlayer.h"

rPlayer::rPlayer() {
    _upA = _viewA = 0;
}

void rPlayer::setPosition(rPoint position) {
    _position = position;
}

void rPlayer::setAngles(float up, float view) {
    while( up >= 360.0 )
        up -= 360.0;
    while( view >= 360.0 )
        view -= 360.0;

    while( up < 0.0 )
        up += 360.0;
    while( view < 0.0 )
        view += 360.0;

    _upA = up;
    _viewA = view;
}

void rPlayer::updateCamera() {
    _up.setCoords  (
                      _position.xPos() + cosf( _upA * M_PI/180 ) * 180/M_PI,
                      _position.yPos() + sinf( _upA * M_PI/180 ) * 180/M_PI,
                      _position.zPos()
                   );
    _view.setCoords(
                      _position.xPos() + cosf( _viewA * M_PI/180 ) * 180/M_PI,
                      _position.yPos(),
                      _position.zPos() + sinf( _viewA * M_PI/180 ) * 180/M_PI
                   );
    gluLookAt      (
                      _position.xPos(), _position.yPos(), _position.zPos(),
                    0, 1, 0,
                      //_view.xPos(), _view.yPos(), _view.zPos(),
                   //   _up.xPos(), _up.yPos(), _up.zPos()
                    0, 1, 0
                   );
}

void rPlayerManager::renderAllViewports() {
    for( tIDList<rPlayer*>::iterator it = list()->begin(); it != list()->end(); it++ )
        (*it)->updateCamera();
}

void rPlayerManager::addPlayer(rPlayer * player) {
    pushID( player );
}

void rPlayerManager::removePlayer(rPlayer * player) {
    deleteID( player );
}
