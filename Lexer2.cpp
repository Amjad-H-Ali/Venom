#include <iostream>
#include <chrono>
#include <fstream>


int main() {

    
    std::chrono::time_point<std::chrono::system_clock> start2, end2;

    start2 = std::chrono::system_clock::now();

    std::ifstream inFile; // 9 Cache-Lines (576 Bytes)

    const uint16_t Buffer_SZ = 2048;  // |
                                      // |  Less than 1 Cache-Line
    uint16_t shift_factor = 0;        // |  
                                      // |  8 Bytes in Total.
    uint32_t i, k ;                   // |

    char fstr[Buffer_SZ] = {0x20}; // 32 Cache-Lines (Blocks)

    uint64_t tokens[Buffer_SZ] = {0}; // 256 Cache-Lines (Blocks)

    inFile.open("new.venom");

    while(inFile) {

        inFile.read(fstr, Buffer_SZ-3);

        while(i < Buffer_SZ) {

            unsigned char offset_x = fstr[i],
                          offset_y = fstr[i+1],
                          offset_z = fstr[i+2];
                      
            bool not_white_space = 
                        offset_x != 0x9 & offset_x != 0xA & offset_x != 0x20,

                 is_letter = 
                        ( // 1 if letters or _ in sequence, 0 otherwise.
                            (
                                (offset_x >= 'A' & offset_x <= 'Z') | 
                                (offset_x >= 'a' & offset_x <= 'z') |
                                (offset_x == '_')
                            ) &

                            (
                                (offset_y >= 'A' & offset_y <= 'Z') | 
                                (offset_y >= 'a' & offset_y <= 'z') |
                                (offset_y == '_')
                            )

                        ),

                 is_operator = 

                        (
                            offset_x == '!' | offset_x == '%'  | 
                            offset_x == '&' | offset_x == '*'  | 
                            offset_x == '+' | offset_x == '^'  | 
                            offset_x == '|' |
                            // Sub, Dot, Division
                            (offset_x >= '-' & offset_x <= '/') |
                            // Less-Than, Equal, Greater-Than
                            (offset_x >= '<' & offset_x <= '>')
                        ) &

                        (
                            offset_y == '*' | offset_y == '+' | 
                            offset_y == '|' | offset_y == '&' |
                            offset_y == '-' |
                            // Less-Than, Equal, Greater-Than
                            (offset_y >= '<' & offset_y <= '>')
                                        
                        );

        
            tokens[k] |=

                ( // Shift result into 64-Bit integer.
            
                    // 128(0) + 0 if fstr[i] is white-space. Otherwise, 128x + y or 128x + 0. Read comment below.
                    not_white_space *

                    (

                        ( 
                            // Mult By 128
                            static_cast<uint64_t>(offset_x) <<7
                        ) +

                        ( // 128x + y if xy are adjacent letters or adjacent operators, otherwise 128x + 0. 

                            (    
                                // 1 if either two adjacent letters or two adjacent operators, 0 otherwise.
                                is_letter |

                                // 1 if compound operator, 0 otherwise.
                                is_operator

                            ) * offset_y
                        )
                    )
                      // Mult By 16
                ) << (shift_factor<<4); 
                

                // Increment shift_factor only if fstr[i], fstr[i+1], and fstr[i+2] 
                // are all letters
                ++shift_factor;
                // Otherwise, reset to 0.
                shift_factor *= (0 + 
                                    ( // 1 if letters or _ in sequence, 0 otherwise.
                                        is_letter & 
                                        
                                        (
                                            (offset_z >= 'A' & offset_z <= 'Z') | 
                                            (offset_z >= 'a' & offset_z <= 'z') |
                                            (offset_z == '_')
                                        )

                                    )
                                ); 
                // Increment to next space in Destination array if at end of current Token.
                // Otherwise, k+=0.
                k += ( // End of Token if shift_factor is 0 at this point. 
                       // However, if current Token is white-space, then k+=0 since WS does not count.
                        !shift_factor & 
                        not_white_space
                     );

                i += ( // Increment iterator by 1 or 2. Read coments below.

                        1 + ( 
                                // 1 if fstr[i+1] is white-space, 0 otherwise.
                                offset_y == 0x9 | 
                                offset_y == 0xA |
                                offset_y == 0x20|
     
                                // 1 if letters or _ in sequence, 0 otherwise.
                                is_letter |

                                // 1 if compound operator, 0 otherwise.
                                is_operator
                            )
                     );


            }

    }
    

    end2 = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds2 = end2 - start2; 
    std::time_t end_time2 = std::chrono::system_clock::to_time_t(end2);

    std::cout << "finished computation at " << std::ctime(&end_time2) 
               << "elapsed time: " << elapsed_seconds2.count() << "s\n"; 

    inFile.close();

    int count = 0;

    for(unsigned t = 0; t <72; ++t) {

        std::cout << tokens[t] << std::endl;

        if(tokens[t] == 9427)
            ++count;
    }

        
        std::cout << tokens[0] << ' '<< tokens[1]   << std::endl;
}