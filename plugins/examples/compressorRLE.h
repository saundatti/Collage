
/* Copyright (c) 2009, Cedric Stalder <cedric.stalder@gmail.com> 
 *
 * This library is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License version 2.1 as published
 * by the Free Software Foundation.
 *  
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
 * details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef EQ_PLUGIN_COMPRESSORRLE
#define EQ_PLUGIN_COMPRESSORRLE

#include "compressor.h"
const uint64_t _rleMarker = 0xF3C553FF64F6477Full; // just a random number

#define WRITE_OUTPUT( name )                                            \
    {                                                                   \
        if( last ## name == _rleMarker )                                \
        {                                                               \
            *(out ## name) = _rleMarker; ++(out ## name);               \
            *(out ## name) = last ## name; ++(out ## name);             \
            *(out ## name) = same ## name; ++(out ## name);             \
        }                                                               \
        else                                                            \
            switch( same ## name )                                      \
            {                                                           \
                case 0:                                                 \
                    break;                                              \
                case 3:                                                 \
                    *(out ## name) = last ## name;                      \
                    ++(out ## name);                                    \
                    /* fall through */                                  \
                case 2:                                                 \
                    *(out ## name) = last ## name;                      \
                    ++(out ## name);                                    \
                    /* fall through */                                  \
                case 1:                                                 \
                    *(out ## name) = last ## name;                      \
                    ++(out ## name);                                    \
                    break;                                              \
                                                                        \
                default:                                                \
                    *(out ## name) = _rleMarker;   ++(out ## name);     \
                    *(out ## name) = last ## name; ++(out ## name);     \
                    *(out ## name) = same ## name; ++(out ## name);     \
                    break;                                              \
            }                                                           \
    }

namespace eq
{
namespace plugin
{

    /**
    * An interace for compressor / uncompressor RLE data 
    *
    */
    class CompressorRLE : public Compressor
        {
        public:
            /** @name CompressorRLE */
            /*@{*/
            /** 
             * Compress data with an algorithm RLE.
             * 
             * @param the number channel.
             */
            CompressorRLE( const uint32_t numChannels )
                        : Compressor( numChannels ){}
            virtual ~CompressorRLE(){} 
            
        protected:
            /** an header for each result of compression */
            struct Header
            {
                Header( uint64_t size64, bool useAlphaBool)
                    : size( size64 )
                    , useAlpha( useAlphaBool ){}

                uint64_t size;
                uint32_t useAlpha;
            };

            /** @name _writeHeader */
            /*@{*/
            /** 
             * write header value for each start buffer result of compression
             */
            void _writeHeader( Result** results, 
                               const Header& header );
           
            /** @name _readHeader */
            /*@{*/
            /** 
             * read header value
             */    
            Header _readHeader( const uint8_t* data8 );
            
            /** @name _setupResults */
            /*@{*/
            /** 
             * compute the number result need for compress data
             */    
            void _setupResults( const uint64_t inSize );
        };
    
}
}
#endif // EQ_PLUGIN_COMPRESSORRLE
