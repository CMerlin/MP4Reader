/*******************************************************************************
 * Copyright (c) 2011, Jean-David Gadina - www.xs-labs.com
 * Distributed under the Boost Software License, Version 1.0.
 * 
 * Boost Software License - Version 1.0 - August 17th, 2003
 * 
 * Permission is hereby granted, free of charge, to any person or organization
 * obtaining a copy of the software and accompanying documentation covered by
 * this license (the "Software") to use, reproduce, display, distribute,
 * execute, and transmit the Software, and to prepare derivative works of the
 * Software, and to permit third-parties to whom the Software is furnished to
 * do so, all subject to the following:
 * 
 * The copyright notices in the Software and this entire statement, including
 * the above license grant, this restriction and the following disclaimer,
 * must be included in all copies of the Software, in whole or in part, and
 * all derivative works of the Software, unless such copies or derivative
 * works are solely in the form of machine-executable object code generated by
 * a source language processor.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
 * SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
 * FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 ******************************************************************************/
 
/* $Id$ */
#include <iostream>
#include <string>
using namespace std;

#include "MP4.Parser.h"
#include "atoms.h"

using namespace MP4;

ParserException::ParserException( void )
{
    this->code = -1;
}

ParserException::ParserException( unsigned int c )
{
    this->code = c;
}

const char * ParserException::what( void ) const throw()
{
    switch( this->code )
    {
        case ParserException::NoFileName:
            
            return "No input file";
    }
    
    return "Unknown exception";
}

Parser::Parser( void )
{
    ParserException e = ParserException( ParserException::NoFileName );
    
    throw e;
}

Parser::Parser( char * filename )
{
    bool                 container;
    uint32_t             length;
    uint64_t             dataLength;
    char                 type[ 5 ];
    char               * data;
    MP4::Atom          * atom;
    MP4::ContainerAtom * containerAtom;
    MP4::ContainerAtom * parentAtom;
    
    this->_stream = new BinaryStream( filename );
    this->_file   = new MP4::File();
    data          = NULL;
    atom          = NULL;
    containerAtom = NULL;
    container     = false;
    parentAtom    = this->_file;
    
    memset( type, 0, 5 );
    
    while( !this->_stream->eof() )
    {
        length     = this->_stream->readBigEndianUnsignedInteger();
        dataLength = 0;
		
        this->_stream->read( ( char * )type, 4 );
		LOG_DBG("atoms type=%s length=%d\n", type, length);
        if( length == 1 )
        {
            //dataLength = this->_stream->readBigEndianUnsignedInteger() - 16;
			dataLength = this->_stream->readBigEndian64() - 16;
        }
        else
        {
            dataLength = length - 8;
        }
       
        /* Container atoms */
        if
        (
               strcmp( type, "dinf" ) == 0
            || strcmp( type, "edts" ) == 0
            || strcmp( type, "ipro" ) == 0
            || strcmp( type, "mdia" ) == 0
            || strcmp( type, "meta" ) == 0
            || strcmp( type, "mfra" ) == 0
            || strcmp( type, "minf" ) == 0
            || strcmp( type, "moof" ) == 0
            || strcmp( type, "moov" ) == 0
            || strcmp( type, "mvex" ) == 0
            || strcmp( type, "sinf" ) == 0
            || strcmp( type, "skip" ) == 0
            || strcmp( type, "stbl" ) == 0
            || strcmp( type, "traf" ) == 0
            || strcmp( type, "trak" ) == 0
        )
        {
            containerAtom = new MP4::ContainerAtom( type );
            
            parentAtom->addChild( containerAtom );
            
            parentAtom = containerAtom;
            
            continue;
        }
        
        /* Data atoms */
        if( strcmp( type, "bxml" ) == 0 )
        {
            atom = ( MP4::Atom * )( new MP4::BXML() );
        }
        else if( strcmp( type, "co64" ) == 0 )
        {
            atom = ( MP4::Atom * )( new MP4::CO64() );
        }
        else if( strcmp( type, "cprt" ) == 0 )
        {
            atom = ( MP4::Atom * )( new MP4::CPRT() );
        }
        else if( strcmp( type, "ctts" ) == 0 )
        {
            atom = ( MP4::Atom * )( new MP4::CTTS() );
        }
        else if( strcmp( type, "dref" ) == 0 )
        {
            atom = ( MP4::Atom * )( new MP4::DREF() );
        }
        else if( strcmp( type, "elst" ) == 0 )
        {
            atom = ( MP4::Atom * )( new MP4::ELST() );
        }
        else if( strcmp( type, "free" ) == 0 )
        {
            atom = ( MP4::Atom * )( new MP4::FREE() );
        }
        else if( strcmp( type, "frma" ) == 0 )
        {
            atom = ( MP4::Atom * )( new MP4::FRMA() );
        }
        else if( strcmp( type, "ftyp" ) == 0 )
        {
            atom = ( MP4::Atom * )( new MP4::FTYP() );
        }
        else if( strcmp( type, "hdlr" ) == 0 )
        {
            atom = ( MP4::Atom * )( new MP4::HDLR() );
        }
        else if( strcmp( type, "hmhd" ) == 0 )
        {
            atom = ( MP4::Atom * )( new MP4::HMHD() );
        }
        else if( strcmp( type, "iinf" ) == 0 )
        {
            atom = ( MP4::Atom * )( new MP4::IINF() );
        }
        else if( strcmp( type, "iloc" ) == 0 )
        {
            atom = ( MP4::Atom * )( new MP4::ILOC() );
        }
        else if( strcmp( type, "imif" ) == 0 )
        {
            atom = ( MP4::Atom * )( new MP4::IMIF() );
        }
        else if( strcmp( type, "ipmc" ) == 0 )
        {
            atom = ( MP4::Atom * )( new MP4::IPMC() );
        }
        else if( strcmp( type, "mdat" ) == 0 )
        {
            atom = ( MP4::Atom * )( new MP4::MDAT() );
        }
        else if( strcmp( type, "mdhd" ) == 0 )
        {
            atom = ( MP4::Atom * )( new MP4::MDHD() );
        }
        else if( strcmp( type, "mehd" ) == 0 )
        {
            atom = ( MP4::Atom * )( new MP4::MEHD() );
        }
        else if( strcmp( type, "mfhd" ) == 0 )
        {
            atom = ( MP4::Atom * )( new MP4::MFHD() );
        }
        else if( strcmp( type, "mfro" ) == 0 )
        {
            atom = ( MP4::Atom * )( new MP4::MFRO() );
        }
        else if( strcmp( type, "mvhd" ) == 0 )
        {
            atom = ( MP4::Atom * )( new MP4::MVHD() );
        }
        else if( strcmp( type, "padb" ) == 0 )
        {
            atom = ( MP4::Atom * )( new MP4::PADB() );
        }
        else if( strcmp( type, "pdin" ) == 0 )
        {
            atom = ( MP4::Atom * )( new MP4::PDIN() );
        }
        else if( strcmp( type, "pitm" ) == 0 )
        {
            atom = ( MP4::Atom * )( new MP4::PITM() );
        }
        else if( strcmp( type, "sbgp" ) == 0 )
        {
            atom = ( MP4::Atom * )( new MP4::SBGP() );
        }
        else if( strcmp( type, "schi" ) == 0 )
        {
            atom = ( MP4::Atom * )( new MP4::SCHI() );
        }
        else if( strcmp( type, "schm" ) == 0 )
        {
            atom = ( MP4::Atom * )( new MP4::SCHM() );
        }
        else if( strcmp( type, "sdtp" ) == 0 )
        {
            atom = ( MP4::Atom * )( new MP4::SDTP() );
        }
        else if( strcmp( type, "sgpd" ) == 0 )
        {
            atom = ( MP4::Atom * )( new MP4::SGPD() );
        }
        else if( strcmp( type, "smhd" ) == 0 )
        {
            atom = ( MP4::Atom * )( new MP4::SMHD() );
        }
        else if( strcmp( type, "subs" ) == 0 )
        {
            atom = ( MP4::Atom * )( new MP4::SUBS() );
        }
        else if( strcmp( type, "stsd" ) == 0 )
        {
            atom = ( MP4::Atom * )( new MP4::STSD() );
        }
        else if( strcmp( type, "stco" ) == 0 )
        {
            atom = ( MP4::Atom * )( new MP4::STCO() );
        }
        else if( strcmp( type, "stdp" ) == 0 )
        {
            atom = ( MP4::Atom * )( new MP4::STDP() );
        }
        else if( strcmp( type, "stsc" ) == 0 )
        {
            atom = ( MP4::Atom * )( new MP4::STSC() );
        }
        else if( strcmp( type, "stsh" ) == 0 )
        {
            atom = ( MP4::Atom * )( new MP4::STSH() );
        }
        else if( strcmp( type, "stss" ) == 0 )
        {
            atom = ( MP4::Atom * )( new MP4::STSS() );
        }
        else if( strcmp( type, "stsz" ) == 0 )
        {
            atom = ( MP4::Atom * )( new MP4::STSZ() );
        }
        else if( strcmp( type, "stts" ) == 0 )
        {
            atom = ( MP4::Atom * )( new MP4::STTS() );
        }
        else if( strcmp( type, "stz2" ) == 0 )
        {
            atom = ( MP4::Atom * )( new MP4::STZ2() );
        }
        else if( strcmp( type, "tfhd" ) == 0 )
        {
            atom = ( MP4::Atom * )( new MP4::TFHD() );
        }
        else if( strcmp( type, "tfra" ) == 0 )
        {
            atom = ( MP4::Atom * )( new MP4::TFRA() );
        }
        else if( strcmp( type, "tkhd" ) == 0 )
        {
            atom = ( MP4::Atom * )( new MP4::TKHD() );
        }
        else if( strcmp( type, "tref" ) == 0 )
        {
            atom = ( MP4::Atom * )( new MP4::TREF() );
        }
        else if( strcmp( type, "trex" ) == 0 )
        {
            atom = ( MP4::Atom * )( new MP4::TREX() );
        }
        else if( strcmp( type, "trun" ) == 0 )
        {
            atom = ( MP4::Atom * )( new MP4::TRUN() );
        }
        else if( strcmp( type, "udta" ) == 0 )
        {
            atom = ( MP4::Atom * )( new MP4::UDTA() );
        }
        else if( strcmp( type, "vmhd" ) == 0 )
        {
            atom = ( MP4::Atom * )( new MP4::VMHD() );
        }
        else if( strcmp( type, "xml " ) == 0 )
        {
            atom = ( MP4::Atom * )( new MP4::XML() );
        }
        else
        {
            atom = new MP4::UnknownAtom( type );
        }
        
        parentAtom->addChild( atom );
        
        ( ( MP4::DataAtom * )atom )->processData( this->_stream, dataLength );
    }

	string str = this->_file->description();
	LOG_DBG("type=%s\n", str.c_str());
    //std::cout << this->_file->description();
}

Parser::~Parser( void )
{
    delete this->_stream;
    delete this->_file;
}
