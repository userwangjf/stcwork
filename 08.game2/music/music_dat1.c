
#include "bsp/config.h"


// CODE u8 music_sin[64] = {
//  0x7F,0x8B,0x98,0xA4,0xB0,0xBB,0xC6,0xD0,0xD9,0xE2,0xE9,0xEF,0xF5,0xF9,0xFC,0xFE
// ,0xFE,0xFE,0xFC,0xF9,0xF5,0xEF,0xE9,0xE2,0xD9,0xD0,0xC6,0xBB,0xB0,0xA4,0x98,0x8B
// ,0x7F,0x73,0x66,0x5A,0x4E,0x43,0x38,0x2E,0x25,0x1C,0x15,0x0F,0x09,0x05,0x02,0x00
// ,0x00,0x00,0x02,0x05,0x09,0x0F,0x15,0x1C,0x25,0x2E,0x38,0x43,0x4E,0x5A,0x66,0x73};

CODE u8 music_line[6268] = {
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x81, 0x80, 0x80, 0x80, 0x80, 0x80, 
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x81, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 
	0x7F, 0x80, 0x81, 0x80, 0x80, 0x7F, 0x80, 0x81, 0x80, 0x7F, 0x80, 0x80, 0x80, 0x81, 0x81, 0x7F, 
	0x7E, 0x80, 0x82, 0x80, 0x7F, 0x80, 0x81, 0x80, 0x7E, 0x81, 0x81, 0x80, 0x7E, 0x80, 0x81, 0x81, 
	0x81, 0x7F, 0x7E, 0x7F, 0x80, 0x81, 0x81, 0x80, 0x7F, 0x80, 0x80, 0x7F, 0x80, 0x80, 0x80, 0x82, 
	0x80, 0x80, 0x7E, 0x7F, 0x80, 0x80, 0x81, 0x80, 0x81, 0x7F, 0x80, 0x80, 0x80, 0x81, 0x80, 0x7F, 
	0x7E, 0x81, 0x82, 0x81, 0x7F, 0x7F, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x81, 0x7F, 0x80, 
	0x80, 0x80, 0x80, 0x80, 0x81, 0x80, 0x7F, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x7F, 0x81, 0x80, 
	0x80, 0x81, 0x81, 0x7F, 0x7E, 0x81, 0x81, 0x81, 0x80, 0x7E, 0x80, 0x7F, 0x80, 0x81, 0x82, 0x80, 
	0x7E, 0x80, 0x80, 0x81, 0x7F, 0x81, 0x80, 0x80, 0x82, 0x7F, 0x80, 0x80, 0x81, 0x80, 0x7F, 0x7E, 
	0x7F, 0x83, 0x82, 0x80, 0x7E, 0x80, 0x80, 0x80, 0x81, 0x80, 0x80, 0x80, 0x7F, 0x7F, 0x81, 0x81, 
	0x80, 0x80, 0x7F, 0x80, 0x80, 0x81, 0x7F, 0x80, 0x80, 0x80, 0x81, 0x80, 0x80, 0x80, 0x7F, 0x7F, 
	0x7F, 0x81, 0x82, 0x80, 0x81, 0x7D, 0x80, 0x7E, 0x84, 0x89, 0x67, 0x81, 0x9A, 0x86, 0x7F, 0x6D, 
	0x6F, 0x75, 0x91, 0x96, 0x89, 0x88, 0x74, 0x79, 0x6C, 0x83, 0x8F, 0x6E, 0x77, 0x85, 0x94, 0x93, 
	0x8B, 0x7B, 0x66, 0x73, 0x79, 0x83, 0x87, 0x84, 0x86, 0x82, 0x85, 0x82, 0x7E, 0x7A, 0x7A, 0x7F, 
	0x82, 0x7B, 0x7F, 0x80, 0x86, 0x8C, 0x6F, 0x88, 0x95, 0x83, 0x76, 0x66, 0x70, 0x7E, 0x96, 0x92, 
	0x88, 0x82, 0x7D, 0x7B, 0x72, 0x76, 0x79, 0x84, 0x8A, 0x89, 0x89, 0x7F, 0x7E, 0x7D, 0x7D, 0x7F, 
	0x83, 0x73, 0x85, 0x8E, 0x6E, 0x78, 0x80, 0x94, 0x8D, 0x89, 0x7C, 0x68, 0x76, 0x76, 0x87, 0x84, 
	0x89, 0x8B, 0x8A, 0x83, 0x76, 0x76, 0x76, 0x83, 0x7F, 0x83, 0x80, 0x81, 0x80, 0x88, 0x80, 0x6C, 
	0x8E, 0x91, 0x82, 0x78, 0x6E, 0x74, 0x7E, 0x8F, 0x8F, 0x8B, 0x80, 0x76, 0x78, 0x7D, 0x7D, 0x79, 
	0x81, 0x85, 0x8D, 0x84, 0x7F, 0x7D, 0x7A, 0x80, 0x82, 0x82, 0x73, 0x8D, 0x85, 0x6B, 0x7D, 0x83, 
	0x90, 0x8C, 0x86, 0x75, 0x6F, 0x78, 0x79, 0x8A, 0x88, 0x88, 0x82, 0x84, 0x81, 0x7A, 0x7C, 0x79, 
	0x80, 0x7E, 0x83, 0x81, 0x82, 0x7F, 0x87, 0x7D, 0x70, 0x91, 0x8D, 0x83, 0x75, 0x6E, 0x73, 0x7F, 
	0x95, 0x8E, 0x8A, 0x7D, 0x76, 0x77, 0x79, 0x7E, 0x7B, 0x86, 0x86, 0x87, 0x82, 0x80, 0x7F, 0x7D, 
	0x7F, 0x80, 0x7F, 0x79, 0x91, 0x7D, 0x6B, 0x7D, 0x84, 0x91, 0x8F, 0x89, 0x71, 0x6E, 0x75, 0x7A, 
	0x88, 0x88, 0x8A, 0x84, 0x85, 0x7D, 0x79, 0x7B, 0x7B, 0x81, 0x7F, 0x84, 0x81, 0x80, 0x7D, 0x89, 
	0x7A, 0x75, 0x94, 0x8A, 0x80, 0x72, 0x6F, 0x75, 0x84, 0x94, 0x8B, 0x89, 0x7D, 0x79, 0x78, 0x7C, 
	0x7C, 0x7B, 0x85, 0x85, 0x88, 0x82, 0x81, 0x7E, 0x7F, 0x7E, 0x80, 0x7B, 0x7B, 0x92, 0x78, 0x70, 
	0x7E, 0x88, 0x92, 0x8C, 0x84, 0x6F, 0x71, 0x77, 0x7D, 0x88, 0x87, 0x88, 0x83, 0x86, 0x7F, 0x7B, 
	0x7A, 0x7B, 0x7F, 0x7F, 0x83, 0x81, 0x81, 0x80, 0x8B, 0x75, 0x79, 0x94, 0x85, 0x7E, 0x71, 0x71, 
	0x76, 0x88, 0x93, 0x8A, 0x89, 0x7B, 0x78, 0x77, 0x7B, 0x7B, 0x7E, 0x85, 0x85, 0x87, 0x82, 0x82, 
	0x7E, 0x7F, 0x7D, 0x81, 0x7A, 0x80, 0x91, 0x72, 0x72, 0x7F, 0x89, 0x91, 0x8B, 0x82, 0x6D, 0x74, 
	0x77, 0x7F, 0x88, 0x88, 0x86, 0x82, 0x86, 0x7C, 0x7C, 0x79, 0x7D, 0x7F, 0x81, 0x82, 0x80, 0x82, 
	0x80, 0x89, 0x73, 0x7E, 0x91, 0x84, 0x7E, 0x6F, 0x73, 0x78, 0x89, 0x91, 0x8C, 0x87, 0x7A, 0x79, 
	0x75, 0x7B, 0x7B, 0x81, 0x86, 0x84, 0x87, 0x81, 0x81, 0x7D, 0x7F, 0x7D, 0x82, 0x78, 0x83, 0x8E, 
	0x70, 0x74, 0x80, 0x8C, 0x90, 0x8A, 0x80, 0x6B, 0x75, 0x80, 0x75, 0x80, 0x99, 0x8E, 0x7F, 0x7C, 
	0x73, 0x75, 0x81, 0x89, 0x80, 0x89, 0x90, 0x71, 0x68, 0x79, 0x82, 0x91, 0x95, 0x87, 0x74, 0x6F, 
	0x7E, 0x74, 0x7C, 0x96, 0x91, 0x83, 0x7B, 0x71, 0x71, 0x7F, 0x8F, 0x86, 0x7F, 0x8F, 0x7E, 0x6A, 
	0x74, 0x7D, 0x89, 0x93, 0x8D, 0x7E, 0x71, 0x7C, 0x78, 0x71, 0x8C, 0x96, 0x88, 0x80, 0x74, 0x6F, 
	0x78, 0x8A, 0x8C, 0x80, 0x8C, 0x87, 0x6B, 0x6F, 0x7D, 0x84, 0x91, 0x8F, 0x83, 0x73, 0x79, 0x7E, 
	0x6F, 0x83, 0x96, 0x8B, 0x82, 0x77, 0x70, 0x76, 0x84, 0x8D, 0x80, 0x86, 0x8D, 0x74, 0x6D, 0x79, 
	0x81, 0x8C, 0x8F, 0x85, 0x76, 0x77, 0x82, 0x74, 0x7A, 0x93, 0x8F, 0x83, 0x7B, 0x70, 0x72, 0x80, 
	0x8F, 0x86, 0x84, 0x8F, 0x7A, 0x68, 0x74, 0x7E, 0x89, 0x92, 0x8B, 0x7C, 0x73, 0x7F, 0x77, 0x73, 
	0x8E, 0x92, 0x86, 0x7E, 0x72, 0x71, 0x7C, 0x89, 0x89, 0x81, 0x8D, 0x85, 0x6B, 0x71, 0x7C, 0x86, 
	0x8F, 0x8C, 0x81, 0x74, 0x7D, 0x7C, 0x6F, 0x85, 0x95, 0x8A, 0x81, 0x77, 0x71, 0x77, 0x86, 0x8D, 
	0x80, 0x88, 0x8C, 0x70, 0x6C, 0x7A, 0x83, 0x8E, 0x8F, 0x85, 0x75, 0x77, 0x80, 0x71, 0x7E, 0x95, 
	0x8E, 0x84, 0x7A, 0x70, 0x74, 0x80, 0x8C, 0x84, 0x86, 0x8F, 0x78, 0x6B, 0x76, 0x7F, 0x8A, 0x90, 
	0x88, 0x7B, 0x75, 0x81, 0x76, 0x75, 0x90, 0x91, 0x85, 0x7D, 0x73, 0x72, 0x7C, 0x8B, 0x88, 0x81, 
	0x8E, 0x81, 0x6B, 0x73, 0x7D, 0x86, 0x8F, 0x8B, 0x80, 0x74, 0x7E, 0x7B, 0x71, 0x89, 0x94, 0x88, 
	0x7F, 0x75, 0x72, 0x79, 0x86, 0x8A, 0x80, 0x8A, 0x89, 0x6F, 0x6F, 0x7B, 0x83, 0x8E, 0x8D, 0x84, 
	0x76, 0x7A, 0x7F, 0x71, 0x7F, 0x94, 0x8B, 0x83, 0x7A, 0x72, 0x75, 0x81, 0x8C, 0x82, 0x85, 0x8E, 
	0x76, 0x6C, 0x79, 0x80, 0x8B, 0x8F, 0x88, 0x79, 0x76, 0x80, 0x74, 0x77, 0x91, 0x90, 0x85, 0x7D, 
	0x72, 0x73, 0x7D, 0x8B, 0x86, 0x82, 0x8E, 0x7F, 0x6B, 0x75, 0x7E, 0x86, 0x8F, 0x8A, 0x7E, 0x75, 
	0x7F, 0x7A, 0x72, 0x8B, 0x93, 0x86, 0x7F, 0x76, 0x72, 0x7A, 0x88, 0x89, 0x80, 0x8B, 0x87, 0x6E, 
	0x71, 0x7D, 0x83, 0x8D, 0x8C, 0x83, 0x76, 0x7F, 0x77, 0x70, 0x8E, 0x90, 0x86, 0x7E, 0x77, 0x75, 
	0x7B, 0x8A, 0x81, 0x84, 0x90, 0x79, 0x6E, 0x79, 0x7F, 0x88, 0x8B, 0x87, 0x79, 0x7D, 0x80, 0x6F, 
	0x81, 0x91, 0x88, 0x82, 0x7A, 0x76, 0x77, 0x85, 0x87, 0x7E, 0x8E, 0x84, 0x6F, 0x76, 0x7D, 0x84, 
	0x8A, 0x8A, 0x7F, 0x77, 0x83, 0x75, 0x75, 0x8F, 0x8C, 0x84, 0x7E, 0x77, 0x75, 0x7F, 0x8A, 0x7F, 
	0x86, 0x8D, 0x74, 0x72, 0x7C, 0x80, 0x88, 0x8B, 0x85, 0x77, 0x7F, 0x7E, 0x70, 0x87, 0x90, 0x85, 
	0x81, 0x7A, 0x76, 0x78, 0x88, 0x85, 0x7F, 0x8F, 0x7F, 0x6F, 0x79, 0x7E, 0x84, 0x8A, 0x89, 0x7C, 
	0x79, 0x83, 0x72, 0x7A, 0x91, 0x89, 0x82, 0x7C, 0x77, 0x76, 0x82, 0x8A, 0x7E, 0x89, 0x8A, 0x71, 
	0x74, 0x7D, 0x82, 0x89, 0x8A, 0x82, 0x76, 0x81, 0x7B, 0x72, 0x8B, 0x8E, 0x84, 0x7F, 0x78, 0x76, 
	0x7B, 0x8A, 0x82, 0x82, 0x8F, 0x7A, 0x6F, 0x7B, 0x80, 0x87, 0x8A, 0x88, 0x79, 0x7A, 0x81, 0x71, 
	0x80, 0x92, 0x88, 0x81, 0x7A, 0x76, 0x77, 0x85, 0x89, 0x7E, 0x8C, 0x86, 0x6F, 0x75, 0x7E, 0x83, 
	0x8A, 0x8A, 0x80, 0x76, 0x82, 0x77, 0x74, 0x8E, 0x8D, 0x84, 0x7E, 0x77, 0x75, 0x7D, 0x8A, 0x81, 
	0x85, 0x8E, 0x76, 0x70, 0x7B, 0x80, 0x88, 0x8B, 0x86, 0x77, 0x7C, 0x7F, 0x70, 0x84, 0x91, 0x86, 
	0x81, 0x7A, 0x75, 0x77, 0x87, 0x87, 0x7F, 0x8E, 0x82, 0x6F, 0x78, 0x7E, 0x84, 0x8A, 0x8A, 0x7E, 
	0x77, 0x82, 0x74, 0x78, 0x8F, 0x8A, 0x84, 0x7E, 0x77, 0x75, 0x7F, 0x8A, 0x80, 0x88, 0x8B, 0x73, 
	0x73, 0x7C, 0x80, 0x88, 0x8A, 0x85, 0x78, 0x7F, 0x7C, 0x71, 0x88, 0x8F, 0x85, 0x81, 0x79, 0x76, 
	0x7A, 0x87, 0x84, 0x81, 0x8F, 0x7E, 0x6F, 0x79, 0x7E, 0x85, 0x8A, 0x88, 0x7C, 0x7A, 0x82, 0x72, 
	0x7C, 0x90, 0x89, 0x83, 0x7C, 0x77, 0x77, 0x81, 0x89, 0x7F, 0x8A, 0x89, 0x72, 0x75, 0x7D, 0x82, 
	0x88, 0x8A, 0x82, 0x77, 0x81, 0x79, 0x72, 0x8B, 0x8D, 0x85, 0x7F, 0x78, 0x75, 0x7B, 0x89, 0x82, 
	0x83, 0x8F, 0x7A, 0x70, 0x7A, 0x7F, 0x86, 0x8A, 0x87, 0x7B, 0x7B, 0x80, 0x71, 0x80, 0x90, 0x87, 
	0x82, 0x7A, 0x77, 0x78, 0x84, 0x88, 0x7E, 0x8C, 0x85, 0x70, 0x77, 0x7E, 0x84, 0x88, 0x8A, 0x80, 
	0x76, 0x82, 0x77, 0x76, 0x8E, 0x8C, 0x83, 0x7E, 0x79, 0x75, 0x7D, 0x8A, 0x80, 0x85, 0x8E, 0x75, 
	0x72, 0x7C, 0x80, 0x87, 0x8A, 0x86, 0x77, 0x81, 0x77, 0x72, 0x8F, 0x8B, 0x83, 0x7D, 0x7A, 0x77, 
	0x7D, 0x89, 0x7D, 0x8E, 0x86, 0x70, 0x78, 0x7E, 0x85, 0x84, 0x89, 0x7E, 0x7B, 0x82, 0x6F, 0x81, 
	0x90, 0x86, 0x80, 0x79, 0x7B, 0x78, 0x86, 0x83, 0x82, 0x90, 0x78, 0x71, 0x7B, 0x83, 0x87, 0x85, 
	0x86, 0x78, 0x81, 0x79, 0x72, 0x8D, 0x8C, 0x84, 0x7B, 0x7A, 0x7A, 0x7D, 0x88, 0x7E, 0x8C, 0x88, 
	0x70, 0x77, 0x7D, 0x85, 0x85, 0x88, 0x80, 0x7A, 0x82, 0x70, 0x7F, 0x90, 0x86, 0x81, 0x7A, 0x7B, 
	0x78, 0x84, 0x83, 0x82, 0x91, 0x7A, 0x71, 0x7B, 0x81, 0x86, 0x86, 0x87, 0x7A, 0x80, 0x7B, 0x70, 
	0x8C, 0x8C, 0x84, 0x7D, 0x7A, 0x79, 0x7B, 0x88, 0x7D, 0x8A, 0x8B, 0x71, 0x76, 0x7D, 0x85, 0x85, 
	0x88, 0x81, 0x79, 0x83, 0x72, 0x7C, 0x90, 0x87, 0x81, 0x7A, 0x7C, 0x77, 0x83, 0x85, 0x7F, 0x91, 
	0x7C, 0x70, 0x7B, 0x81, 0x86, 0x85, 0x88, 0x7A, 0x7F, 0x7D, 0x70, 0x8A, 0x8D, 0x84, 0x7D, 0x7A, 
	0x7A, 0x7B, 0x88, 0x7F, 0x89, 0x8B, 0x72, 0x75, 0x7D, 0x85, 0x85, 0x88, 0x83, 0x79, 0x82, 0x73, 
	0x7B, 0x90, 0x88, 0x82, 0x7A, 0x7B, 0x77, 0x82, 0x86, 0x80, 0x90, 0x7E, 0x70, 0x79, 0x80, 0x86, 
	0x86, 0x88, 0x7B, 0x7E, 0x7E, 0x6F, 0x88, 0x8E, 0x85, 0x7F, 0x7A, 0x7A, 0x79, 0x88, 0x80, 0x87, 
	0x8D, 0x73, 0x75, 0x7C, 0x84, 0x85, 0x87, 0x84, 0x78, 0x83, 0x74, 0x78, 0x8F, 0x88, 0x82, 0x7A, 
	0x7B, 0x78, 0x80, 0x86, 0x7F, 0x90, 0x81, 0x70, 0x79, 0x7F, 0x86, 0x85, 0x89, 0x7D, 0x7D, 0x7F, 
	0x6F, 0x85, 0x8E, 0x86, 0x7F, 0x7A, 0x7A, 0x78, 0x87, 0x81, 0x86, 0x8F, 0x75, 0x74, 0x7C, 0x83, 
	0x86, 0x87, 0x85, 0x79, 0x83, 0x76, 0x75, 0x8F, 0x89, 0x83, 0x7B, 0x7B, 0x79, 0x7E, 0x87, 0x7E, 
	0x8F, 0x84, 0x70, 0x78, 0x7E, 0x85, 0x84, 0x88, 0x7E, 0x7C, 0x81, 0x6F, 0x82, 0x8F, 0x86, 0x7F, 
	0x7A, 0x7B, 0x79, 0x86, 0x81, 0x84, 0x90, 0x77, 0x73, 0x7C, 0x83, 0x86, 0x85, 0x86, 0x79, 0x82, 
	0x78, 0x74, 0x8D, 0x8A, 0x83, 0x7B, 0x7B, 0x79, 0x7D, 0x88, 0x7D, 0x8C, 0x86, 0x71, 0x78, 0x7E, 
	0x86, 0x84, 0x87, 0x7F, 0x7B, 0x82, 0x71, 0x81, 0x8F, 0x85, 0x80, 0x7A, 0x7C, 0x78, 0x85, 0x83, 
	0x82, 0x90, 0x78, 0x72, 0x7C, 0x82, 0x86, 0x86, 0x87, 0x79, 0x80, 0x79, 0x73, 0x8D, 0x8B, 0x84, 
	0x7B, 0x7B, 0x79, 0x7E, 0x86, 0x81, 0x91, 0x7D, 0x70, 0x7A, 0x81, 0x88, 0x83, 0x86, 0x7B, 0x81, 
	0x74, 0x77, 0x91, 0x87, 0x83, 0x77, 0x7D, 0x7A, 0x83, 0x82, 0x84, 0x90, 0x72, 0x76, 0x7B, 0x86, 
	0x86, 0x84, 0x82, 0x7A, 0x83, 0x6D, 0x84, 0x8F, 0x86, 0x7F, 0x77, 0x7D, 0x7A, 0x88, 0x7D, 0x8C, 
	0x88, 0x6F, 0x79, 0x7C, 0x8A, 0x83, 0x87, 0x7C, 0x7E, 0x7D, 0x71, 0x8E, 0x89, 0x85, 0x79, 0x79, 
	0x7B, 0x7F, 0x87, 0x7E, 0x91, 0x7A, 0x72, 0x7A, 0x81, 0x8A, 0x83, 0x86, 0x78, 0x83, 0x73, 0x7A, 
	0x92, 0x86, 0x83, 0x76, 0x7D, 0x78, 0x85, 0x82, 0x85, 0x90, 0x71, 0x76, 0x7B, 0x86, 0x86, 0x85, 
	0x81, 0x7A, 0x82, 0x6E, 0x86, 0x8E, 0x85, 0x7E, 0x77, 0x7D, 0x7A, 0x88, 0x7D, 0x8D, 0x85, 0x6F, 
	0x79, 0x7D, 0x8A, 0x83, 0x87, 0x7B, 0x80, 0x7B, 0x71, 0x90, 0x89, 0x85, 0x79, 0x7B, 0x7B, 0x7F, 
	0x86, 0x7F, 0x92, 0x79, 0x72, 0x7A, 0x82, 0x89, 0x83, 0x85, 0x78, 0x84, 0x72, 0x7C, 0x91, 0x86, 
	0x83, 0x76, 0x7D, 0x79, 0x86, 0x80, 0x85, 0x8E, 0x70, 0x77, 0x7B, 0x88, 0x85, 0x85, 0x80, 0x7B, 
	0x82, 0x6E, 0x89, 0x8D, 0x85, 0x7D, 0x77, 0x7D, 0x7B, 0x88, 0x7D, 0x8E, 0x83, 0x6F, 0x79, 0x7D, 
	0x8A, 0x83, 0x88, 0x7A, 0x80, 0x79, 0x73, 0x90, 0x89, 0x85, 0x78, 0x7B, 0x7A, 0x81, 0x86, 0x7F, 
	0x91, 0x77, 0x73, 0x7A, 0x83, 0x89, 0x83, 0x85, 0x78, 0x84, 0x71, 0x7E, 0x91, 0x86, 0x83, 0x76, 
	0x7E, 0x78, 0x86, 0x80, 0x87, 0x8E, 0x70, 0x77, 0x7A, 0x88, 0x85, 0x86, 0x80, 0x7C, 0x82, 0x6E, 
	0x89, 0x8C, 0x85, 0x7D, 0x78, 0x7D, 0x7B, 0x88, 0x7C, 0x8F, 0x82, 0x6F, 0x7A, 0x7E, 0x8A, 0x82, 
	0x87, 0x7A, 0x81, 0x79, 0x73, 0x90, 0x88, 0x85, 0x78, 0x7C, 0x7A, 0x80, 0x84, 0x80, 0x92, 0x76, 
	0x74, 0x7A, 0x83, 0x88, 0x83, 0x85, 0x79, 0x84, 0x71, 0x7F, 0x90, 0x85, 0x82, 0x76, 0x7E, 0x78, 
	0x87, 0x7F, 0x88, 0x8C, 0x6F, 0x78, 0x7B, 0x89, 0x85, 0x86, 0x7E, 0x7C, 0x80, 0x6E, 0x8B, 0x8C, 
	0x85, 0x7C, 0x79, 0x7C, 0x7C, 0x88, 0x7D, 0x90, 0x81, 0x6F, 0x7A, 0x7F, 0x89, 0x83, 0x88, 0x79, 
	0x82, 0x78, 0x74, 0x91, 0x88, 0x84, 0x77, 0x7C, 0x78, 0x82, 0x85, 0x81, 0x91, 0x75, 0x72, 0x7A, 
	0x85, 0x87, 0x85, 0x83, 0x7C, 0x7C, 0x71, 0x8A, 0x8D, 0x84, 0x7C, 0x77, 0x7D, 0x7F, 0x84, 0x87, 
	0x8D, 0x74, 0x72, 0x7C, 0x84, 0x8A, 0x83, 0x80, 0x7D, 0x78, 0x76, 0x8E, 0x8C, 0x82, 0x7B, 0x76, 
	0x7E, 0x80, 0x84, 0x89, 0x88, 0x72, 0x75, 0x7E, 0x85, 0x89, 0x82, 0x7F, 0x7D, 0x75, 0x7B, 0x90, 
	0x89, 0x80, 0x79, 0x78, 0x7F, 0x82, 0x84, 0x8C, 0x82, 0x6F, 0x79, 0x7F, 0x87, 0x87, 0x82, 0x7E, 
	0x7C, 0x73, 0x81, 0x91, 0x86, 0x80, 0x77, 0x7A, 0x7F, 0x82, 0x85, 0x8C, 0x7D, 0x70, 0x7B, 0x80, 
	0x89, 0x85, 0x81, 0x7E, 0x7A, 0x74, 0x87, 0x90, 0x83, 0x7E, 0x76, 0x7C, 0x80, 0x82, 0x87, 0x8B, 
	0x76, 0x72, 0x7D, 0x82, 0x89, 0x83, 0x80, 0x7E, 0x78, 0x76, 0x8C, 0x8D, 0x82, 0x7C, 0x78, 0x7E, 
	0x81, 0x83, 0x89, 0x88, 0x72, 0x75, 0x7E, 0x85, 0x88, 0x82, 0x7F, 0x7D, 0x76, 0x7A, 0x90, 0x89, 
	0x81, 0x79, 0x78, 0x7F, 0x81, 0x84, 0x8B, 0x84, 0x6F, 0x78, 0x7F, 0x87, 0x87, 0x81, 0x7F, 0x7B, 
	0x74, 0x7F, 0x92, 0x86, 0x80, 0x78, 0x7A, 0x7F, 0x81, 0x85, 0x8C, 0x7E, 0x6F, 0x7B, 0x80, 0x88, 
	0x86, 0x81, 0x7F, 0x7A, 0x73, 0x86, 0x90, 0x84, 0x7F, 0x77, 0x7C, 0x7F, 0x82, 0x87, 0x8C, 0x78, 
	0x71, 0x7D, 0x81, 0x89, 0x84, 0x81, 0x7E, 0x78, 0x75, 0x8B, 0x8D, 0x82, 0x7D, 0x77, 0x7E, 0x80, 
	0x83, 0x89, 0x8A, 0x73, 0x74, 0x7E, 0x84, 0x89, 0x82, 0x80, 0x7D, 0x76, 0x78, 0x8F, 0x8A, 0x81, 
	0x7A, 0x78, 0x7E, 0x81, 0x84, 0x8B, 0x85, 0x70, 0x77, 0x7F, 0x86, 0x88, 0x82, 0x80, 0x7C, 0x74, 
	0x7E, 0x91, 0x86, 0x81, 0x78, 0x7A, 0x7F, 0x81, 0x85, 0x8C, 0x80, 0x6F, 0x7B, 0x80, 0x88, 0x86, 
	0x81, 0x7F, 0x7B, 0x74, 0x84, 0x91, 0x84, 0x7F, 0x77, 0x7C, 0x80, 0x82, 0x86, 0x8B, 0x79, 0x71, 
	0x7D, 0x82, 0x89, 0x84, 0x80, 0x7E, 0x79, 0x75, 0x8A, 0x8E, 0x82, 0x7C, 0x77, 0x7E, 0x81, 0x83, 
	0x88, 0x8A, 0x75, 0x73, 0x7E, 0x84, 0x89, 0x82, 0x80, 0x7D, 0x77, 0x78, 0x8E, 0x8B, 0x81, 0x7A, 
	0x77, 0x7E, 0x81, 0x83, 0x8A, 0x87, 0x71, 0x76, 0x7F, 0x86, 0x88, 0x81, 0x7F, 0x7D, 0x75, 0x7C, 
	0x91, 0x87, 0x80, 0x78, 0x79, 0x7F, 0x81, 0x85, 0x8B, 0x81, 0x6F, 0x7A, 0x80, 0x88, 0x86, 0x81, 
	0x7F, 0x7B, 0x74, 0x82, 0x91, 0x84, 0x7F, 0x77, 0x7B, 0x80, 0x81, 0x86, 0x8C, 0x7C, 0x70, 0x7D, 
	0x80, 0x8A, 0x83, 0x83, 0x7E, 0x72, 0x7C, 0x8C, 0x8A, 0x80, 0x7B, 0x78, 0x80, 0x80, 0x8A, 0x8B, 
	0x77, 0x73, 0x7B, 0x83, 0x88, 0x84, 0x80, 0x7C, 0x72, 0x80, 0x8F, 0x88, 0x80, 0x78, 0x79, 0x80, 
	0x81, 0x8C, 0x89, 0x75, 0x74, 0x7D, 0x84, 0x89, 0x82, 0x80, 0x7B, 0x72, 0x83, 0x8F, 0x87, 0x80, 
	0x77, 0x79, 0x7F, 0x82, 0x8D, 0x87, 0x73, 0x74, 0x7D, 0x85, 0x89, 0x81, 0x81, 0x79, 0x72, 0x85, 
	0x8F, 0x86, 0x7F, 0x77, 0x7A, 0x7F, 0x82, 0x8E, 0x85, 0x72, 0x75, 0x7E, 0x86, 0x88, 0x82, 0x81, 
	0x77, 0x73, 0x87, 0x8D, 0x86, 0x7F, 0x77, 0x7B, 0x7F, 0x83, 0x8F, 0x82, 0x72, 0x77, 0x7E, 0x86, 
	0x88, 0x81, 0x80, 0x76, 0x75, 0x89, 0x8D, 0x85, 0x7D, 0x76, 0x7D, 0x80, 0x86, 0x8E, 0x7F, 0x72, 
	0x78, 0x80, 0x87, 0x87, 0x81, 0x80, 0x74, 0x78, 0x8B, 0x8B, 0x83, 0x7C, 0x77, 0x7E, 0x80, 0x87, 
	0x8E, 0x7C, 0x72, 0x7A, 0x80, 0x88, 0x86, 0x80, 0x7F, 0x73, 0x7A, 0x8D, 0x8A, 0x82, 0x7B, 0x77, 
	0x7E, 0x80, 0x89, 0x8D, 0x79, 0x72, 0x7B, 0x81, 0x89, 0x85, 0x80, 0x7D, 0x72, 0x7C, 0x8E, 0x89, 
	0x82, 0x7A, 0x78, 0x7F, 0x81, 0x8A, 0x8B, 0x77, 0x73, 0x7B, 0x82, 0x89, 0x84, 0x80, 0x7C, 0x71, 
	0x7F, 0x8E, 0x88, 0x81, 0x78, 0x78, 0x7F, 0x81, 0x8C, 0x89, 0x75, 0x74, 0x7C, 0x83, 0x8A, 0x84, 
	0x81, 0x7A, 0x71, 0x82, 0x8E, 0x87, 0x81, 0x78, 0x79, 0x7F, 0x82, 0x8E, 0x88, 0x74, 0x75, 0x7C, 
	0x84, 0x89, 0x82, 0x81, 0x79, 0x72, 0x85, 0x8E, 0x86, 0x80, 0x77, 0x7B, 0x80, 0x82, 0x8E, 0x85, 
	0x72, 0x77, 0x7E, 0x85, 0x88, 0x81, 0x81, 0x78, 0x74, 0x87, 0x8D, 0x85, 0x7E, 0x77, 0x7C, 0x7F, 
	0x83, 0x8F, 0x82, 0x73, 0x78, 0x7E, 0x86, 0x88, 0x81, 0x80, 0x76, 0x75, 0x89, 0x8C, 0x84, 0x7D, 
	0x76, 0x7C, 0x80, 0x85, 0x8E, 0x7F, 0x72, 0x79, 0x7F, 0x88, 0x86, 0x80, 0x80, 0x74, 0x78, 0x8B, 
	0x8B, 0x83, 0x7C, 0x77, 0x7E, 0x7F, 0x87, 0x8E, 0x7C, 0x72, 0x7A, 0x80, 0x88, 0x85, 0x80, 0x7F, 
	0x73, 0x7A, 0x8D, 0x8A, 0x82, 0x7B, 0x78, 0x7F, 0x7F, 0x88, 0x8D, 0x7A, 0x72, 0x7A, 0x81, 0x88, 
	0x85, 0x81, 0x7E, 0x72, 0x7C, 0x8E, 0x89, 0x82, 0x7A, 0x78, 0x7F, 0x80, 0x8A, 0x8B, 0x77, 0x73, 
	0x7B, 0x83, 0x89, 0x83, 0x81, 0x7C, 0x72, 0x80, 0x8E, 0x88, 0x82, 0x78, 0x7A, 0x7C, 0x82, 0x91, 
	0x80, 0x74, 0x79, 0x7D, 0x87, 0x86, 0x84, 0x7C, 0x6F, 0x80, 0x8D, 0x87, 0x82, 0x79, 0x7A, 0x7C, 
	0x85, 0x91, 0x7F, 0x73, 0x78, 0x7E, 0x87, 0x86, 0x84, 0x7B, 0x6E, 0x82, 0x8E, 0x88, 0x82, 0x78, 
	0x7A, 0x7D, 0x87, 0x92, 0x7F, 0x71, 0x78, 0x7E, 0x88, 0x87, 0x83, 0x7A, 0x6E, 0x81, 0x8F, 0x88, 
	0x81, 0x78, 0x79, 0x7C, 0x86, 0x92, 0x7F, 0x71, 0x77, 0x7E, 0x88, 0x87, 0x84, 0x7B, 0x6E, 0x81, 
	0x8E, 0x89, 0x81, 0x77, 0x7A, 0x7C, 0x87, 0x91, 0x7E, 0x73, 0x77, 0x7E, 0x88, 0x86, 0x84, 0x7A, 
	0x6F, 0x82, 0x8D, 0x87, 0x81, 0x78, 0x7A, 0x7C, 0x87, 0x90, 0x7E, 0x73, 0x78, 0x7E, 0x88, 0x86, 
	0x83, 0x7A, 0x6F, 0x83, 0x8D, 0x87, 0x81, 0x78, 0x7B, 0x7D, 0x87, 0x90, 0x7D, 0x73, 0x78, 0x7F, 
	0x88, 0x86, 0x83, 0x79, 0x6F, 0x84, 0x8E, 0x87, 0x80, 0x78, 0x7B, 0x7D, 0x89, 0x90, 0x7D, 0x72, 
	0x78, 0x7F, 0x88, 0x86, 0x83, 0x78, 0x6F, 0x84, 0x8E, 0x87, 0x80, 0x77, 0x7A, 0x7D, 0x88, 0x91, 
	0x7C, 0x73, 0x78, 0x7F, 0x89, 0x86, 0x84, 0x78, 0x6F, 0x85, 0x8E, 0x88, 0x80, 0x77, 0x7A, 0x7D, 
	0x89, 0x91, 0x7C, 0x72, 0x77, 0x7F, 0x89, 0x87, 0x84, 0x78, 0x70, 0x84, 0x8D, 0x88, 0x80, 0x77, 
	0x7A, 0x7D, 0x89, 0x90, 0x7C, 0x73, 0x77, 0x7F, 0x88, 0x86, 0x84, 0x78, 0x6F, 0x85, 0x8D, 0x88, 
	0x81, 0x77, 0x7A, 0x7C, 0x89, 0x90, 0x7B, 0x73, 0x78, 0x7F, 0x88, 0x86, 0x84, 0x78, 0x70, 0x85, 
	0x8D, 0x87, 0x80, 0x78, 0x7B, 0x7D, 0x89, 0x90, 0x7B, 0x73, 0x78, 0x80, 0x88, 0x85, 0x84, 0x77, 
	0x70, 0x86, 0x8D, 0x87, 0x7F, 0x77, 0x7B, 0x7D, 0x8A, 0x8F, 0x7A, 0x73, 0x78, 0x80, 0x89, 0x85, 
	0x83, 0x77, 0x71, 0x86, 0x8D, 0x87, 0x7F, 0x77, 0x7B, 0x7D, 0x8A, 0x8F, 0x7A, 0x73, 0x78, 0x80, 
	0x88, 0x85, 0x84, 0x76, 0x70, 0x87, 0x8D, 0x87, 0x7F, 0x77, 0x7B, 0x7D, 0x8A, 0x8F, 0x7A, 0x72, 
	0x79, 0x80, 0x89, 0x86, 0x83, 0x76, 0x70, 0x87, 0x8D, 0x87, 0x7F, 0x77, 0x7A, 0x7D, 0x8B, 0x8F, 
	0x7A, 0x73, 0x78, 0x80, 0x88, 0x86, 0x84, 0x77, 0x71, 0x86, 0x8D, 0x87, 0x7F, 0x77, 0x7B, 0x7D, 
	0x8A, 0x8F, 0x7A, 0x73, 0x78, 0x80, 0x88, 0x85, 0x84, 0x76, 0x71, 0x87, 0x8C, 0x86, 0x7F, 0x77, 
	0x7B, 0x7D, 0x8B, 0x8E, 0x79, 0x75, 0x79, 0x81, 0x88, 0x86, 0x83, 0x6E, 0x79, 0x8C, 0x87, 0x85, 
	0x7B, 0x7A, 0x77, 0x88, 0x94, 0x7B, 0x76, 0x77, 0x7F, 0x85, 0x87, 0x86, 0x6E, 0x77, 0x8C, 0x89, 
	0x87, 0x7C, 0x7A, 0x77, 0x86, 0x95, 0x7D, 0x74, 0x77, 0x7D, 0x86, 0x87, 0x87, 0x6F, 0x74, 0x8B, 
	0x89, 0x87, 0x7C, 0x7A, 0x77, 0x83, 0x96, 0x80, 0x75, 0x77, 0x7C, 0x85, 0x86, 0x88, 0x72, 0x72, 
	0x8A, 0x89, 0x87, 0x7D, 0x7B, 0x78, 0x81, 0x95, 0x81, 0x74, 0x77, 0x7B, 0x85, 0x86, 0x88, 0x74, 
	0x70, 0x89, 0x8A, 0x88, 0x7E, 0x79, 0x78, 0x7F, 0x95, 0x84, 0x74, 0x77, 0x7A, 0x85, 0x86, 0x89, 
	0x76, 0x6E, 0x88, 0x8A, 0x88, 0x7F, 0x79, 0x78, 0x7D, 0x95, 0x87, 0x74, 0x77, 0x79, 0x84, 0x86, 
	0x8A, 0x78, 0x6C, 0x86, 0x8B, 0x88, 0x81, 0x7A, 0x79, 0x7B, 0x93, 0x89, 0x75, 0x77, 0x79, 0x83, 
	0x85, 0x89, 0x7B, 0x6C, 0x84, 0x8C, 0x88, 0x82, 0x7A, 0x7A, 0x7A, 0x92, 0x8C, 0x75, 0x77, 0x78, 
	0x83, 0x85, 0x88, 0x7D, 0x6B, 0x82, 0x8C, 0x88, 0x83, 0x7A, 0x79, 0x79, 0x90, 0x8E, 0x76, 0x77, 
	0x78, 0x81, 0x86, 0x89, 0x7F, 0x6B, 0x7F, 0x8C, 0x88, 0x84, 0x7B, 0x7A, 0x78, 0x8D, 0x90, 0x77, 
	0x76, 0x78, 0x80, 0x85, 0x88, 0x82, 0x6B, 0x7D, 0x8D, 0x88, 0x84, 0x7B, 0x7B, 0x77, 0x8B, 0x92, 
	0x79, 0x76, 0x78, 0x80, 0x85, 0x87, 0x83, 0x6C, 0x7A, 0x8C, 0x89, 0x85, 0x7B, 0x7A, 0x77, 0x89, 
	0x93, 0x7B, 0x75, 0x77, 0x7E, 0x86, 0x88, 0x85, 0x6D, 0x77, 0x8C, 0x89, 0x87, 0x7C, 0x7A, 0x77, 
	0x86, 0x95, 0x7D, 0x75, 0x78, 0x7D, 0x85, 0x87, 0x86, 0x6F, 0x75, 0x8B, 0x89, 0x87, 0x7D, 0x7A, 
	0x77, 0x84, 0x95, 0x7E, 0x75, 0x77, 0x7C, 0x85, 0x87, 0x88, 0x71, 0x73, 0x8B, 0x8A, 0x87, 0x7D, 
	0x7A, 0x77, 0x82, 0x95, 0x81, 0x74, 0x77, 0x7C, 0x85, 0x86, 0x88, 0x73, 0x70, 0x89, 0x8A, 0x88, 
	0x7E, 0x7A, 0x78, 0x7F, 0x95, 0x84, 0x75, 0x77, 0x7B, 0x84, 0x86, 0x89, 0x76, 0x6F, 0x87, 0x8A, 
	0x88, 0x80, 0x7A, 0x78, 0x7D, 0x94, 0x86, 0x75, 0x77, 0x7A, 0x83, 0x86, 0x89, 0x78, 0x6E, 0x86, 
	0x8A, 0x87, 0x81, 0x7A, 0x79, 0x7C, 0x93, 0x88, 0x75, 0x78, 0x7A, 0x83, 0x85, 0x89, 0x7A, 0x6C, 
	0x85, 0x8B, 0x87, 0x81, 0x7A, 0x7A, 0x7A, 0x92, 0x8A, 0x75, 0x77, 0x79, 0x83, 0x85, 0x8B, 0x75, 
	0x6F, 0x8A, 0x86, 0x87, 0x7D, 0x7C, 0x75, 0x87, 0x96, 0x78, 0x7B, 0x76, 0x7F, 0x83, 0x8A, 0x7D, 
	0x69, 0x87, 0x86, 0x89, 0x81, 0x7C, 0x77, 0x80, 0x99, 0x7C, 0x7A, 0x76, 0x7D, 0x83, 0x88, 0x85, 
	0x68, 0x82, 0x87, 0x89, 0x84, 0x7B, 0x79, 0x79, 0x98, 0x81, 0x79, 0x79, 0x79, 0x83, 0x85, 0x89, 
	0x6A, 0x7D, 0x89, 0x86, 0x87, 0x7C, 0x7C, 0x76, 0x95, 0x87, 0x76, 0x7B, 0x78, 0x83, 0x83, 0x8C, 
	0x6E, 0x76, 0x8B, 0x84, 0x89, 0x7C, 0x7D, 0x74, 0x90, 0x8E, 0x76, 0x7B, 0x76, 0x82, 0x82, 0x8C, 
	0x74, 0x6F, 0x8B, 0x84, 0x8A, 0x7E, 0x7E, 0x75, 0x89, 0x94, 0x77, 0x7B, 0x76, 0x80, 0x82, 0x8A, 
	0x7C, 0x6A, 0x88, 0x85, 0x89, 0x80, 0x7D, 0x77, 0x82, 0x98, 0x7A, 0x7A, 0x77, 0x7E, 0x83, 0x88, 
	0x82, 0x68, 0x85, 0x88, 0x88, 0x83, 0x7C, 0x79, 0x7C, 0x99, 0x7F, 0x78, 0x79, 0x7B, 0x84, 0x85, 
	0x88, 0x69, 0x7E, 0x8A, 0x86, 0x86, 0x7B, 0x7C, 0x77, 0x96, 0x86, 0x76, 0x7B, 0x78, 0x84, 0x83, 
	0x8B, 0x6D, 0x76, 0x8B, 0x85, 0x89, 0x7C, 0x7D, 0x74, 0x91, 0x8D, 0x75, 0x7C, 0x77, 0x83, 0x82, 
	0x8C, 0x73, 0x70, 0x8C, 0x84, 0x89, 0x7D, 0x7D, 0x75, 0x8A, 0x93, 0x76, 0x7B, 0x76, 0x81, 0x82, 
	0x8A, 0x7A, 0x6A, 0x8A, 0x85, 0x89, 0x80, 0x7D, 0x76, 0x82, 0x98, 0x79, 0x7A, 0x77, 0x7E, 0x83, 
	0x89, 0x82, 0x67, 0x85, 0x87, 0x88, 0x83, 0x7C, 0x79, 0x7B, 0x99, 0x7F, 0x78, 0x78, 0x7B, 0x84, 
	0x86, 0x88, 0x68, 0x7F, 0x89, 0x86, 0x86, 0x7B, 0x7B, 0x77, 0x97, 0x85, 0x76, 0x7A, 0x78, 0x84, 
	0x84, 0x8B, 0x6C, 0x78, 0x8B, 0x85, 0x88, 0x7C, 0x7C, 0x75, 0x92, 0x8C, 0x75, 0x7C, 0x77, 0x83, 
	0x83, 0x8C, 0x72, 0x71, 0x8B, 0x84, 0x8A, 0x7D, 0x7D, 0x74, 0x8A, 0x92, 0x77, 0x7C, 0x76, 0x81, 
	0x82, 0x8C, 0x7A, 0x6C, 0x89, 0x84, 0x8A, 0x80, 0x7D, 0x75, 0x82, 0x96, 0x79, 0x7B, 0x77, 0x7F, 
	0x82, 0x89, 0x81, 0x69, 0x85, 0x86, 0x88, 0x82, 0x7C, 0x79, 0x7C, 0x98, 0x7D, 0x79, 0x7A, 0x7C, 
	0x83, 0x85, 0x87, 0x69, 0x80, 0x89, 0x86, 0x85, 0x7B, 0x7C, 0x77, 0x96, 0x85, 0x76, 0x7B, 0x79, 
	0x83, 0x84, 0x8B, 0x6C, 0x78, 0x8A, 0x85, 0x88, 0x7C, 0x7C, 0x75, 0x92, 0x8C, 0x76, 0x7B, 0x77, 
	0x82, 0x83, 0x8C, 0x72, 0x72, 0x8B, 0x85, 0x88, 0x7F, 0x7A, 0x76, 0x90, 0x89, 0x76, 0x7E, 0x7A, 
	0x81, 0x86, 0x83, 0x6D, 0x7F, 0x89, 0x82, 0x85, 0x7C, 0x79, 0x86, 0x91, 0x7B, 0x7B, 0x7C, 0x7C, 
	0x85, 0x84, 0x73, 0x76, 0x8A, 0x83, 0x85, 0x80, 0x79, 0x81, 0x90, 0x81, 0x77, 0x7D, 0x79, 0x83, 
	0x87, 0x79, 0x72, 0x87, 0x85, 0x83, 0x84, 0x79, 0x7D, 0x8E, 0x88, 0x77, 0x7E, 0x7A, 0x7E, 0x87, 
	0x7E, 0x70, 0x82, 0x88, 0x81, 0x84, 0x7D, 0x7A, 0x89, 0x8E, 0x79, 0x7B, 0x7D, 0x7D, 0x85, 0x82, 
	0x72, 0x7A, 0x8B, 0x82, 0x84, 0x7E, 0x79, 0x84, 0x91, 0x7F, 0x78, 0x7E, 0x7C, 0x84, 0x85, 0x76, 
	0x74, 0x89, 0x85, 0x83, 0x81, 0x78, 0x7F, 0x90, 0x86, 0x77, 0x7D, 0x7A, 0x81, 0x88, 0x7B, 0x70, 
	0x84, 0x88, 0x82, 0x84, 0x7A, 0x7A, 0x8C, 0x8D, 0x78, 0x7C, 0x7C, 0x7D, 0x87, 0x82, 0x70, 0x7C, 
	0x8A, 0x83, 0x85, 0x7E, 0x77, 0x85, 0x91, 0x7D, 0x79, 0x7D, 0x7B, 0x85, 0x85, 0x75, 0x75, 0x89, 
	0x84, 0x85, 0x81, 0x77, 0x80, 0x90, 0x84, 0x78, 0x7D, 0x7A, 0x82, 0x87, 0x7A, 0x71, 0x85, 0x86, 
	0x83, 0x84, 0x79, 0x7B, 0x8E, 0x8B, 0x78, 0x7D, 0x7A, 0x7E, 0x88, 0x80, 0x70, 0x7E, 0x89, 0x82, 
	0x85, 0x7D, 0x78, 0x87, 0x90, 0x7C, 0x7A, 0x7C, 0x7B, 0x85, 0x84, 0x73, 0x77, 0x8A, 0x83, 0x85, 
	0x80, 0x78, 0x81, 0x90, 0x82, 0x78, 0x7E, 0x79, 0x82, 0x87, 0x78, 0x72, 0x86, 0x86, 0x83, 0x84, 
	0x79, 0x7C, 0x8E, 0x89, 0x78, 0x7E, 0x7B, 0x7F, 0x87, 0x7E, 0x70, 0x81, 0x88, 0x82, 0x85, 0x7C, 
	0x79, 0x88, 0x8E, 0x7A, 0x7C, 0x7C, 0x7C, 0x86, 0x84, 0x72, 0x79, 0x8A, 0x83, 0x85, 0x7F, 0x78, 
	0x82, 0x90, 0x80, 0x79, 0x7D, 0x7B, 0x83, 0x87, 0x78, 0x73, 0x88, 0x85, 0x84, 0x83, 0x79, 0x7D, 
	0x8F, 0x86, 0x78, 0x7D, 0x7A, 0x80, 0x88, 0x7D, 0x70, 0x83, 0x87, 0x83, 0x85, 0x7B, 0x7A, 0x8B, 
	0x8C, 0x79, 0x7D, 0x7B, 0x7D, 0x86, 0x82, 0x70, 0x7C, 0x8A, 0x82, 0x85, 0x7E, 0x78, 0x85, 0x90, 
	0x7D, 0x7A, 0x7D, 0x7B, 0x84, 0x85, 0x75, 0x75, 0x89, 0x83, 0x84, 0x82, 0x78, 0x7F, 0x90, 0x84, 
	0x78, 0x7E, 0x7A, 0x81, 0x88, 0x7B, 0x71, 0x85, 0x86, 0x83, 0x84, 0x7A, 0x7B, 0x8C, 0x8A, 0x78, 
	0x7E, 0x7B, 0x7E, 0x87, 0x80, 0x71, 0x7E, 0x89, 0x81, 0x86, 0x7D, 0x78, 0x86, 0x8F, 0x7B, 0x7B, 
	0x7D, 0x7A, 0x86, 0x84, 0x74, 0x77, 0x8A, 0x81, 0x86, 0x7F, 0x78, 0x87, 0x8A, 0x7E, 0x7C, 0x80, 
	0x7C, 0x87, 0x7B, 0x74, 0x82, 0x83, 0x82, 0x82, 0x7C, 0x81, 0x8E, 0x82, 0x7D, 0x7F, 0x7C, 0x82, 
	0x80, 0x73, 0x7B, 0x86, 0x81, 0x83, 0x7E, 0x7D, 0x8C, 0x88, 0x7C, 0x7D, 0x7D, 0x7F, 0x84, 0x77, 
	0x75, 0x84, 0x84, 0x83, 0x81, 0x7A, 0x86, 0x8D, 0x7F, 0x7B, 0x7E, 0x7D, 0x85, 0x7D, 0x72, 0x7F, 
	0x86, 0x82, 0x83, 0x7C, 0x7F, 0x8E, 0x86, 0x7B, 0x7E, 0x7C, 0x81, 0x83, 0x75, 0x78, 0x85, 0x83, 
	0x83, 0x80, 0x7B, 0x89, 0x8B, 0x7D, 0x7D, 0x7E, 0x7E, 0x84, 0x7B, 0x73, 0x82, 0x85, 0x82, 0x82, 
	0x7A, 0x82, 0x8E, 0x82, 0x7B, 0x7E, 0x7C, 0x84, 0x81, 0x73, 0x7B, 0x86, 0x83, 0x84, 0x7D, 0x7B, 
	0x8C, 0x89, 0x7C, 0x7D, 0x7C, 0x7F, 0x85, 0x78, 0x75, 0x85, 0x84, 0x82, 0x81, 0x7A, 0x85, 0x8E, 
	0x7F, 0x7B, 0x7E, 0x7D, 0x85, 0x7F, 0x72, 0x7E, 0x86, 0x82, 0x83, 0x7C, 0x7E, 0x8D, 0x86, 0x7B, 
	0x7D, 0x7C, 0x81, 0x84, 0x76, 0x78, 0x85, 0x83, 0x83, 0x80, 0x7A, 0x88, 0x8C, 0x7E, 0x7C, 0x7C, 
	0x7D, 0x85, 0x7B, 0x73, 0x82, 0x85, 0x82, 0x83, 0x7B, 0x81, 0x8E, 0x83, 0x7B, 0x7E, 0x7C, 0x82, 
	0x82, 0x73, 0x7B, 0x86, 0x82, 0x83, 0x7E, 0x7C, 0x8B, 0x89, 0x7C, 0x7D, 0x7D, 0x7F, 0x85, 0x78, 
	0x75, 0x84, 0x84, 0x83, 0x81, 0x7A, 0x85, 0x8E, 0x80, 0x7C, 0x7D, 0x7C, 0x84, 0x7F, 0x73, 0x7E, 
	0x86, 0x82, 0x84, 0x7C, 0x7E, 0x8D, 0x86, 0x7B, 0x7E, 0x7C, 0x80, 0x83, 0x75, 0x78, 0x86, 0x83, 
	0x82, 0x80, 0x7A, 0x88, 0x8D, 0x7D, 0x7C, 0x7D, 0x7D, 0x85, 0x7B, 0x73, 0x81, 0x86, 0x82, 0x82, 
	0x7B, 0x81, 0x8F, 0x84, 0x7B, 0x7E, 0x7C, 0x83, 0x82, 0x73, 0x7A, 0x86, 0x83, 0x83, 0x7E, 0x7B, 
	0x8B, 0x8A, 0x7C, 0x7D, 0x7C, 0x7E, 0x85, 0x78, 0x74, 0x84, 0x84, 0x82, 0x82, 0x7A, 0x85, 0x8E, 
	0x80, 0x7C, 0x7D, 0x7B, 0x84, 0x7F, 0x73, 0x7E, 0x86, 0x81, 0x83, 0x7C, 0x7D, 0x8D, 0x87, 0x7B, 
	0x7E, 0x7C, 0x80, 0x84, 0x76, 0x78, 0x86, 0x83, 0x82, 0x80, 0x7A, 0x88, 0x8C, 0x7D, 0x7C, 0x7E, 
	0x7D, 0x84, 0x7B, 0x73, 0x82, 0x86, 0x81, 0x82, 0x7A, 0x81, 0x8F, 0x83, 0x7A, 0x7E, 0x7C, 0x83, 
	0x83, 0x73, 0x79, 0x87, 0x83, 0x83, 0x7F, 0x7B, 0x8B, 0x8B, 0x7C, 0x7D, 0x7D, 0x7E, 0x86, 0x79, 
	0x74, 0x84, 0x84, 0x84, 0x7F, 0x7C, 0x89, 0x86, 0x80, 0x80, 0x7D, 0x82, 0x7F, 0x74, 0x7D, 0x83, 
	0x7F, 0x82, 0x7B, 0x84, 0x8D, 0x82, 0x81, 0x81, 0x80, 0x82, 0x76, 0x75, 0x82, 0x80, 0x81, 0x7E, 
	0x7D, 0x8C, 0x88, 0x81, 0x82, 0x7D, 0x81, 0x7D, 0x72, 0x7C, 0x82, 0x7F, 0x82, 0x7C, 0x85, 0x8D, 
	0x82, 0x81, 0x80, 0x7E, 0x82, 0x76, 0x75, 0x82, 0x80, 0x81, 0x7F, 0x7F, 0x8D, 0x88, 0x7F, 0x81, 
	0x7D, 0x81, 0x7E, 0x72, 0x7D, 0x83, 0x80, 0x81, 0x7B, 0x86, 0x8F, 0x83, 0x7F, 0x7E, 0x7D, 0x84, 
	0x78, 0x75, 0x82, 0x81, 0x82, 0x7E, 0x7D, 0x8D, 0x8A, 0x80, 0x80, 0x7C, 0x81, 0x80, 0x73, 0x7C, 
	0x82, 0x7F, 0x82, 0x7B, 0x84, 0x8E, 0x83, 0x80, 0x7F, 0x7D, 0x82, 0x78, 0x76, 0x81, 0x80, 0x81, 
	0x7F, 0x7D, 0x8C, 0x89, 0x80, 0x80, 0x7D, 0x81, 0x7E, 0x73, 0x7D, 0x82, 0x80, 0x82, 0x7C, 0x84, 
	0x8D, 0x83, 0x80, 0x7F, 0x7E, 0x83, 0x77, 0x75, 0x82, 0x80, 0x82, 0x7E, 0x7C, 0x8C, 0x89, 0x7F, 
	0x81, 0x7D, 0x81, 0x80, 0x73, 0x7C, 0x82, 0x80, 0x82, 0x7B, 0x83, 0x8E, 0x84, 0x81, 0x7F, 0x7D, 
	0x83, 0x78, 0x75, 0x82, 0x80, 0x82, 0x7F, 0x7C, 0x8B, 0x8A, 0x80, 0x81, 0x7D, 0x81, 0x7F, 0x72, 
	0x7C, 0x83, 0x80, 0x82, 0x7B, 0x83, 0x8E, 0x84, 0x80, 0x7F, 0x7E, 0x83, 0x78, 0x75, 0x82, 0x80, 
	0x81, 0x7F, 0x7C, 0x8B, 0x8A, 0x80, 0x81, 0x7D, 0x81, 0x80, 0x72, 0x7C, 0x83, 0x7F, 0x82, 0x7B, 
	0x82, 0x8E, 0x84, 0x80, 0x7F, 0x7D, 0x83, 0x78, 0x74, 0x82, 0x81, 0x82, 0x7F, 0x7C, 0x8B, 0x8A, 
	0x80, 0x81, 0x7D, 0x81, 0x80, 0x73, 0x7B, 0x83, 0x80, 0x82, 0x7B, 0x82, 0x8E, 0x84, 0x81, 0x80, 
	0x7D, 0x83, 0x79, 0x74, 0x82, 0x81, 0x81, 0x7F, 0x7B, 0x8B, 0x8A, 0x80, 0x81, 0x7C, 0x80, 0x80, 
	0x72, 0x7B, 0x83, 0x80, 0x82, 0x7B, 0x82, 0x8E, 0x84, 0x80, 0x80, 0x7C, 0x83, 0x78, 0x74, 0x82, 
	0x81, 0x82, 0x7F, 0x7B, 0x8A, 0x8B, 0x81, 0x81, 0x7C, 0x81, 0x81, 0x73, 0x7A, 0x82, 0x80, 0x82, 
	0x7B, 0x82, 0x8E, 0x84, 0x81, 0x80, 0x7D, 0x83, 0x78, 0x74, 0x81, 0x80, 0x81, 0x7F, 0x7C, 0x8A, 
	0x8A, 0x80, 0x82, 0x7D, 0x80, 0x80, 0x73, 0x7B, 0x83, 0x7F, 0x82, 0x7C, 0x82, 0x8E, 0x84, 0x80, 
	0x80, 0x7D, 0x83, 0x79, 0x73, 0x81, 0x81, 0x81, 0x80, 0x7B, 0x8A, 0x8B, 0x81, 0x81, 0x7D, 0x82, 
	0x7A, 0x75, 0x83, 0x7E, 0x7F, 0x7A, 0x7F, 0x8D, 0x83, 0x83, 0x84, 0x85, 0x82, 0x72, 0x78, 0x81, 
	0x7D, 0x7C, 0x79, 0x88, 0x8C, 0x81, 0x87, 0x86, 0x87, 0x7A, 0x6E, 0x7D, 0x7F, 0x7E, 0x79, 0x7B, 
	0x8F, 0x87, 0x82, 0x87, 0x86, 0x86, 0x71, 0x71, 0x80, 0x7E, 0x7F, 0x78, 0x83, 0x90, 0x84, 0x85, 
	0x85, 0x87, 0x7F, 0x6C, 0x78, 0x80, 0x7E, 0x7D, 0x79, 0x8B, 0x8B, 0x83, 0x88, 0x84, 0x86, 0x75, 
	0x6E, 0x7E, 0x7F, 0x7F, 0x7A, 0x7F, 0x90, 0x85, 0x85, 0x88, 0x85, 0x81, 0x6D, 0x74, 0x82, 0x7F, 
	0x7E, 0x77, 0x87, 0x8F, 0x84, 0x88, 0x85, 0x84, 0x79, 0x6B, 0x7C, 0x81, 0x7F, 0x7B, 0x7A, 0x8E, 
	0x8A, 0x85, 0x88, 0x84, 0x83, 0x70, 0x70, 0x80, 0x7F, 0x7F, 0x78, 0x82, 0x90, 0x86, 0x87, 0x85, 
	0x84, 0x7E, 0x6C, 0x77, 0x81, 0x7F, 0x7E, 0x78, 0x8A, 0x8D, 0x84, 0x88, 0x84, 0x85, 0x76, 0x6C, 
	0x7E, 0x80, 0x80, 0x7B, 0x7C, 0x8F, 0x87, 0x86, 0x88, 0x83, 0x81, 0x6D, 0x72, 0x81, 0x80, 0x80, 
	0x77, 0x84, 0x8F, 0x85, 0x89, 0x85, 0x84, 0x7B, 0x6B, 0x7B, 0x81, 0x7F, 0x7B, 0x79, 0x8E, 0x8B, 
	0x85, 0x88, 0x83, 0x83, 0x72, 0x6F, 0x80, 0x80, 0x80, 0x79, 0x80, 0x90, 0x86, 0x87, 0x86, 0x84, 
	0x7F, 0x6C, 0x76, 0x81, 0x7F, 0x7E, 0x78, 0x8A, 0x8E, 0x84, 0x88, 0x84, 0x85, 0x77, 0x6C, 0x7D, 
	0x7F, 0x7F, 0x7B, 0x7C, 0x8F, 0x88, 0x85, 0x88, 0x84, 0x82, 0x6E, 0x71, 0x81, 0x7F, 0x7F, 0x77, 
	0x84, 0x90, 0x85, 0x88, 0x86, 0x85, 0x7B, 0x6B, 0x79, 0x81, 0x7F, 0x7C, 0x79, 0x8D, 0x8B, 0x84, 
	0x88, 0x84, 0x85, 0x73, 0x6E, 0x7F, 0x7F, 0x7F, 0x79, 0x7F, 0x90, 0x86, 0x86, 0x86, 0x84, 0x80, 
	0x6D, 0x75, 0x81, 0x7E, 0x7E, 0x78, 0x88, 0x8E, 0x83, 0x88, 0x85, 0x85, 0x78, 0x6C, 0x7D, 0x81, 
	0x80, 0x7B, 0x7B, 0x8E, 0x88, 0x85, 0x88, 0x84, 0x83, 0x70, 0x71, 0x81, 0x7E, 0x7E, 0x78, 0x84, 
	0x91, 0x84, 0x87, 0x85, 0x84, 0x7D, 0x6C, 0x79, 0x80, 0x7F, 0x7D, 0x78, 0x8B, 0x8B, 0x84, 0x88, 
	0x84, 0x85, 0x75, 0x6E, 0x7E, 0x7F, 0x7F, 0x79, 0x7E, 0x90, 0x88, 0x86, 0x86, 0x84, 0x81, 0x6D, 
	0x74, 0x81, 0x7E, 0x7F, 0x78, 0x87, 0x8F, 0x84, 0x87, 0x84, 0x84, 0x79, 0x6B, 0x7C, 0x80, 0x7F, 
	0x7C, 0x7B, 0x8F, 0x88, 0x85, 0x86, 0x85, 0x81, 0x6B, 0x7B, 0x7E, 0x7E, 0x79, 0x7A, 0x8E, 0x80, 
	0x89, 0x89, 0x8D, 0x82, 0x6C, 0x7D, 0x76, 0x7D, 0x74, 0x81, 0x8B, 0x7E, 0x8E, 0x8B, 0x94, 0x79, 
	0x70, 0x79, 0x73, 0x7C, 0x73, 0x8B, 0x85, 0x81, 0x8C, 0x8E, 0x93, 0x74, 0x76, 0x75, 0x74, 0x76, 
	0x77, 0x90, 0x80, 0x86, 0x8A, 0x94, 0x8E, 0x70, 0x79, 0x70, 0x76, 0x72, 0x7F, 0x8F, 0x7E, 0x89, 
	0x8B, 0x98, 0x83, 0x72, 0x79, 0x6F, 0x76, 0x71, 0x89, 0x8A, 0x7F, 0x89, 0x8C, 0x97, 0x7B, 0x77, 
	0x75, 0x70, 0x74, 0x74, 0x8F, 0x83, 0x82, 0x89, 0x92, 0x93, 0x74, 0x79, 0x71, 0x73, 0x71, 0x7B, 
	0x91, 0x80, 0x87, 0x89, 0x96, 0x89, 0x73, 0x7A, 0x6F, 0x75, 0x6F, 0x85, 0x8E, 0x7F, 0x88, 0x8A, 
	0x99, 0x80, 0x77, 0x77, 0x6E, 0x74, 0x71, 0x8D, 0x87, 0x82, 0x8A, 0x8F, 0x96, 0x77, 0x79, 0x73, 
	0x71, 0x72, 0x76, 0x90, 0x82, 0x86, 0x89, 0x94, 0x8E, 0x74, 0x7B, 0x6F, 0x73, 0x6F, 0x80, 0x90, 
	0x80, 0x89, 0x89, 0x98, 0x85, 0x76, 0x79, 0x6D, 0x74, 0x6F, 0x8A, 0x8B, 0x80, 0x89, 0x8C, 0x99, 
	0x7C, 0x78, 0x74, 0x6F, 0x72, 0x73, 0x8F, 0x84, 0x85, 0x8A, 0x91, 0x92, 0x75, 0x7B, 0x71, 0x72, 
	0x6F, 0x7A, 0x90, 0x81, 0x88, 0x88, 0x96, 0x89, 0x75, 0x7B, 0x6E, 0x74, 0x6E, 0x84, 0x8D, 0x80, 
	0x8A, 0x8A, 0x99, 0x80, 0x77, 0x77, 0x6E, 0x74, 0x70, 0x8C, 0x87, 0x83, 0x8A, 0x8F, 0x96, 0x78, 
	0x7A, 0x72, 0x71, 0x71, 0x76, 0x90, 0x81, 0x87, 0x89, 0x94, 0x8D, 0x75, 0x7C, 0x6F, 0x74, 0x6F, 
	0x80, 0x8F, 0x7F, 0x89, 0x89, 0x98, 0x85, 0x76, 0x79, 0x6E, 0x74, 0x6F, 0x89, 0x8A, 0x81, 0x8A, 
	0x8C, 0x97, 0x7B, 0x79, 0x75, 0x70, 0x73, 0x74, 0x90, 0x84, 0x85, 0x88, 0x91, 0x92, 0x76, 0x7C, 
	0x71, 0x73, 0x70, 0x7B, 0x90, 0x80, 0x88, 0x89, 0x95, 0x89, 0x75, 0x7A, 0x6F, 0x75, 0x6F, 0x84, 
	0x8D, 0x81, 0x89, 0x8A, 0x97, 0x7E, 0x77, 0x77, 0x70, 0x74, 0x71, 0x8D, 0x86, 0x84, 0x89, 0x8E, 
	0x94, 0x77, 0x7B, 0x72, 0x72, 0x72, 0x77, 0x90, 0x82, 0x87, 0x88, 0x94, 0x8D, 0x75, 0x7B, 0x70, 
	0x73, 0x6E, 0x7F, 0x8E, 0x81, 0x89, 0x8A, 0x96, 0x83, 0x76, 0x79, 0x6F, 0x75, 0x70, 0x88, 0x8A, 
	0x81, 0x89, 0x8C, 0x97, 0x7B, 0x7A, 0x76, 0x70, 0x72, 0x73, 0x8E, 0x83, 0x86, 0x89, 0x92, 0x8F, 
	0x77, 0x7B, 0x72, 0x72, 0x6E, 0x83, 0x87, 0x7E, 0x8A, 0x8F, 0x91, 0x80, 0x84, 0x76, 0x69, 0x6E, 
	0x7D, 0x83, 0x7F, 0x8E, 0x91, 0x8C, 0x84, 0x85, 0x79, 0x69, 0x6F, 0x7B, 0x7E, 0x7F, 0x8F, 0x91, 
	0x89, 0x85, 0x86, 0x79, 0x6B, 0x71, 0x7B, 0x7A, 0x81, 0x8F, 0x91, 0x89, 0x86, 0x84, 0x75, 0x6D, 
	0x73, 0x7B, 0x7A, 0x83, 0x91, 0x90, 0x87, 0x85, 0x82, 0x73, 0x6F, 0x78, 0x7C, 0x79, 0x85, 0x91, 
	0x8D, 0x87, 0x88, 0x7F, 0x6F, 0x6E, 0x7A, 0x7D, 0x7B, 0x88, 0x90, 0x8C, 0x86, 0x87, 0x7C, 0x6D, 
	0x70, 0x7C, 0x7D, 0x7D, 0x8B, 0x90, 0x89, 0x85, 0x87, 0x7A, 0x6C, 0x72, 0x7D, 0x7D, 0x81, 0x8E, 
	0x8F, 0x87, 0x85, 0x84, 0x76, 0x6D, 0x75, 0x7E, 0x7C, 0x84, 0x90, 0x8E, 0x86, 0x85, 0x83, 0x73, 
	0x6E, 0x77, 0x7D, 0x7C, 0x87, 0x92, 0x8C, 0x84, 0x85, 0x80, 0x70, 0x6F, 0x7A, 0x7D, 0x7C, 0x89, 
	0x91, 0x8A, 0x83, 0x86, 0x7E, 0x6F, 0x70, 0x7B, 0x7D, 0x7E, 0x8B, 0x91, 0x89, 0x83, 0x85, 0x7B, 
	0x6E, 0x73, 0x7D, 0x7D, 0x80, 0x8E, 0x8F, 0x87, 0x84, 0x85, 0x77, 0x6D, 0x75, 0x7E, 0x7C, 0x82, 
	0x8F, 0x8E, 0x86, 0x85, 0x83, 0x73, 0x6E, 0x77, 0x7F, 0x7C, 0x85, 0x91, 0x8D, 0x85, 0x85, 0x80, 
	0x71, 0x6E, 0x79, 0x7E, 0x7D, 0x88, 0x91, 0x8C, 0x84, 0x84, 0x7D, 0x6F, 0x70, 0x7B, 0x7E, 0x7E, 
	0x8A, 0x91, 0x8A, 0x84, 0x85, 0x7A, 0x6D, 0x71, 0x7C, 0x7D, 0x7F, 0x8E, 0x91, 0x88, 0x85, 0x84, 
	0x77, 0x6C, 0x73, 0x7D, 0x7C, 0x82, 0x90, 0x90, 0x87, 0x84, 0x83, 0x74, 0x6D, 0x76, 0x7E, 0x7C, 
	0x84, 0x91, 0x8E, 0x85, 0x85, 0x82, 0x72, 0x6D, 0x78, 0x7E, 0x7D, 0x87, 0x91, 0x8C, 0x85, 0x85, 
	0x7F, 0x6F, 0x6F, 0x7A, 0x7D, 0x7D, 0x8A, 0x91, 0x8B, 0x84, 0x85, 0x7C, 0x6E, 0x71, 0x7D, 0x7D, 
	0x7E, 0x8C, 0x90, 0x88, 0x84, 0x86, 0x79, 0x6D, 0x73, 0x7E, 0x7C, 0x80, 0x8F, 0x90, 0x86, 0x84, 
	0x85, 0x77, 0x6D, 0x75, 0x7E, 0x7C, 0x82, 0x8F, 0x8E, 0x86, 0x86, 0x83, 0x73, 0x6D, 0x77, 0x7E, 
	0x7C, 0x86, 0x90, 0x8D, 0x85, 0x85, 0x80, 0x71, 0x6F, 0x7A, 0x7E, 0x7C, 0x87, 0x90, 0x8C, 0x85, 
	0x85, 0x7D, 0x6F, 0x70, 0x7C, 0x7E, 0x7D, 0x8A, 0x91, 0x89, 0x83, 0x86, 0x7B, 0x6F, 0x71, 0x7D, 
	0x7D, 0x7F, 0x8D, 0x8F, 0x89, 0x7F, 0x89, 0x7D, 0x6A, 0x6C, 0x74, 0x87, 0x91, 0x93, 0x85, 0x7F, 
	0x7B, 0x77, 0x7C, 0x7D, 0x7F, 0x7E, 0x85, 0x84, 0x82, 0x80, 0x7F, 0x81, 0x81, 0x81, 0x7D, 0x7F, 
	0x7E, 0x7E, 0x80, 0x81, 0x82, 0x82, 0x82, 0x80, 0x80, 0x7E, 0x7F, 0x80, 0x81, 0x81, 0x80, 0x80, 
	0x7F, 0x7F, 0x80, 0x80, 0x80, 0x81, 0x82, 0x81, 0x7F, 0x7F, 0x7D, 0x7D, 0x80, 0x81, 0x81, 0x81, 
	0x82, 0x82, 0x80, 0x7E, 0x7D, 0x7E, 0x7F, 0x80, 0x81, 0x81, 0x81, 0x82, 0x82, 0x80, 0x7F, 0x7E, 
	0x7E, 0x7F, 0x81, 0x82, 0x81, 0x81, 0x81, 0x80, 0x80, 0x7F, 0x7F, 0x7F, 0x80, 0x80, 0x80, 0x80, 
	0x80, 0x81, 0x80, 0x80, 0x80, 0x80, 0x80, 0x7F, 0x80, 0x80, 0x80, 0x80, 0x81, 0x80, 0x80, 0x80, 
	0x80, 0x80, 0x80, 0x80, 0x7F, 0x80, 0x81, 0x80, 0x80, 0x80, 0x80, 0x7F, 0x80, 0x81, 0x80, 0x80, 
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x81, 0x80, 0x7F, 0x80, 0x80, 0x80, 0x80, 0x80, 
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 
	0x7F, 0x80, 0x81, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 
	0x80, 0x80, 0x80, 0x80, 0x7F, 0x80, 0x80, 0x80, 0x80, 0x80, 0x81, 0x80, 0x80, 0x80, 0x80, 0x80, 
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80
};
