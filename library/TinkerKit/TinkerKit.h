
/*
 *      This program is free software; you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation; either version 2 of the License, or
 *      (at your option) any later version.
 *      
 *      This program is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 *      
 *      You should have received a copy of the GNU General Public License
 *      along with this program; if not, write to the Free Software
 *      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *      MA 02110-1301, USA.
 */

#ifndef TinkerKit_h
#define TinkerKit_h

// Minimum Analog In/Out that each platform have
#define I0 A0
#define I1 A1
#define I2 A2
#define I3 A3
#define I4 A4
#define I5 A5

#define O0 11
#define O1 10
#define O2 9
#define O3 6
#define O4 5
#define O5 3

// Mega have more I/O
#if defined(__AVR_ATmega2560__) || defined(__AVR_ATmega1280__)
#define I6 A6
#define I7 A7
#define I8 A8
#define I9 A9

#define D13 13
#define D12 12
#define D8 8
#define D7 7
#define D4 4
#define D2 2
#endif




class TinkerKit
{

public:
	// Initialise
  TinkerKit(); 

  
protected:

};

#endif


