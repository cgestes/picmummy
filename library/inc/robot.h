///////////////////////////////////////////////////////////////
//              Fichier de Définition des matrices           //
//                    des rotation du robot                  //
//                                                UTC 2007   //
///////////////////////////////////////////////////////////////
 
 
// Définition de la structure de la matrice des définitions
#define DIMX 0
#define DIMY 1
#define DX 2
#define DY 3
#define INDICE_DEBUT_ROT 4
#define INDICE_FIN_ROT 5
 
int Mat_definition_rotation[360][6]={{2,4,0,2,0,14},
     {2,4,0,2,0,14},
     {2,4,0,2,0,14},
     {3,4,1,2,15,34},
     {3,4,1,2,15,34},
     {3,4,1,2,35,54},
     {3,4,1,2,35,54},
     {3,4,1,2,35,54},
     {3,4,1,2,35,54},
     {3,4,1,2,35,54},
     {3,4,1,2,35,54},
     {3,4,1,2,35,54},
     {3,4,1,2,35,54},
     {3,4,1,2,35,54},
     {3,4,1,2,35,54},
     {3,4,1,2,35,54},
     {3,4,1,2,35,54},
     {3,4,1,2,35,54},
     {3,4,1,2,35,54},
     {3,4,1,2,35,54},
     {3,4,1,2,35,54},
     {3,4,1,2,35,54},
     {3,4,1,2,35,54},
     {3,4,1,2,35,54},
     {3,4,1,2,35,54},
     {3,4,1,2,35,54},
     {3,4,1,2,55,74},
     {3,4,1,2,75,94},
     {3,4,1,2,95,114},
     {3,4,1,2,95,114},
     {3,4,1,2,95,114},
     {3,4,1,2,95,114},
     {3,4,1,2,95,114},
     {3,4,1,2,95,114},
     {4,4,2,2,115,139},
     {4,4,2,2,115,139},
     {4,4,2,2,115,139},
     {4,4,2,2,115,139},
     {4,4,2,2,115,139},
     {4,4,2,2,115,139},
     {4,4,2,2,140,164},
     {4,4,2,2,140,164},
     {4,4,2,2,140,164},
     {4,4,2,2,140,164},
     {4,4,2,2,140,164},
     {4,4,2,2,140,164},
     {4,4,2,2,140,164},
     {4,4,2,2,140,164},
     {4,4,2,2,140,164},
     {4,4,2,2,140,164},
     {4,4,2,2,140,164},
     {4,4,2,2,165,189},
     {4,4,2,2,165,189},
     {4,4,2,2,165,189},
     {4,4,2,2,165,189},
     {4,4,2,2,165,189},
     {4,4,2,2,165,189},
     {4,3,2,1,140,159},
     {4,3,2,1,140,159},
     {4,3,2,1,140,159},
     {4,3,2,1,140,159},
     {4,3,2,1,140,159},
     {4,3,2,1,140,159},
     {4,3,2,1,190,209},
     {4,3,2,1,210,229},
     {4,3,2,1,230,249},
     {4,3,2,1,230,249},
     {4,3,2,1,230,249},
     {4,3,2,1,230,249},
     {4,3,2,1,230,249},
     {4,3,2,1,230,249},
     {4,3,2,1,230,249},
     {4,3,2,1,230,249},
     {4,3,2,1,230,249},
     {4,3,2,1,230,249},
     {4,3,2,1,230,249},
     {4,3,2,1,230,249},
     {4,3,2,1,230,249},
     {4,3,2,1,230,249},
     {4,3,2,1,230,249},
     {4,3,2,1,230,249},
     {4,3,2,1,230,249},
     {4,3,2,1,230,249},
     {4,3,2,1,230,249},
     {4,3,2,1,230,249},
     {4,3,2,1,230,249},
     {4,3,2,1,250,269},
     {4,3,2,1,250,269},
     {4,2,2,0,210,224},
     {4,2,2,0,210,224},
     {4,2,2,0,210,224},
     {4,2,2,0,210,224},
     {4,2,2,0,210,224},
     {4,3,2,1,270,289},
     {4,3,2,1,270,289},
     {4,3,2,1,290,309},
     {4,3,2,1,290,309},
     {4,3,2,1,290,309},
     {4,3,2,1,290,309},
     {4,3,2,1,290,309},
     {4,3,2,1,290,309},
     {4,3,2,1,290,309},
     {4,3,2,1,290,309},
     {4,3,2,1,290,309},
     {4,3,2,1,290,309},
     {4,3,2,1,290,309},
     {4,3,2,1,290,309},
     {4,3,2,1,290,309},
     {4,3,2,1,290,309},
     {4,3,2,1,290,309},
     {4,3,2,1,290,309},
     {4,3,2,1,290,309},
     {4,3,2,1,290,309},
     {4,3,2,1,290,309},
     {4,3,2,1,290,309},
     {4,3,2,1,290,309},
     {4,3,2,1,310,329},
     {4,3,2,1,330,349},
     {4,3,2,1,350,369},
     {4,3,2,1,350,369},
     {4,3,2,1,350,369},
     {4,3,2,1,350,369},
     {4,3,2,1,350,369},
     {4,3,2,1,350,369},
     {4,4,2,2,370,394},
     {4,4,2,2,370,394},
     {4,4,2,2,370,394},
     {4,4,2,2,370,394},
     {4,4,2,2,370,394},
     {4,4,2,2,370,394},
     {4,4,2,2,395,419},
     {4,4,2,2,395,419},
     {4,4,2,2,395,419},
     {4,4,2,2,395,419},
     {4,4,2,2,395,419},
     {4,4,2,2,395,419},
     {4,4,2,2,395,419},
     {4,4,2,2,395,419},
     {4,4,2,2,395,419},
     {4,4,2,2,395,419},
     {4,4,2,2,395,419},
     {4,4,2,2,420,444},
     {4,4,2,2,420,444},
     {4,4,2,2,420,444},
     {4,4,2,2,420,444},
     {4,4,2,2,420,444},
     {4,4,2,2,420,444},
     {3,4,2,2,445,464},
     {3,4,2,2,445,464},
     {3,4,2,2,445,464},
     {3,4,2,2,445,464},
     {3,4,2,2,445,464},
     {3,4,2,2,445,464},
     {3,4,2,2,465,484},
     {3,4,2,2,485,504},
     {3,4,2,2,505,524},
     {3,4,2,2,505,524},
     {3,4,2,2,505,524},
     {3,4,2,2,505,524},
     {3,4,2,2,505,524},
     {3,4,2,2,505,524},
     {3,4,2,2,505,524},
     {3,4,2,2,505,524},
     {3,4,2,2,505,524},
     {3,4,2,2,505,524},
     {3,4,2,2,505,524},
     {3,4,2,2,505,524},
     {3,4,2,2,505,524},
     {3,4,2,2,505,524},
     {3,4,2,2,505,524},
     {3,4,2,2,505,524},
     {3,4,2,2,505,524},
     {3,4,2,2,505,524},
     {3,4,2,2,505,524},
     {3,4,2,2,505,524},
     {3,4,2,2,505,524},
     {3,4,2,2,525,544},
     {3,4,2,2,525,544},
     {2,4,2,2,2,16},
     {2,4,2,2,2,16},
     {2,4,2,2,2,16},
     {2,4,2,2,2,16},
     {2,4,2,2,2,16},
     {3,4,2,2,545,564},
     {3,4,2,2,545,564},
     {3,4,2,2,565,584},
     {3,4,2,2,565,584},
     {3,4,2,2,565,584},
     {3,4,2,2,565,584},
     {3,4,2,2,565,584},
     {3,4,2,2,565,584},
     {3,4,2,2,565,584},
     {3,4,2,2,565,584},
     {3,4,2,2,565,584},
     {3,4,2,2,565,584},
     {3,4,2,2,565,584},
     {3,4,2,2,565,584},
     {3,4,2,2,565,584},
     {3,4,2,2,565,584},
     {3,4,2,2,565,584},
     {3,4,2,2,565,584},
     {3,4,2,2,565,584},
     {3,4,2,2,565,584},
     {3,4,2,2,565,584},
     {3,4,2,2,565,584},
     {3,4,2,2,565,584},
     {3,4,2,2,51,70},
     {3,4,2,2,585,604},
     {3,4,2,2,605,624},
     {3,4,2,2,605,624},
     {3,4,2,2,605,624},
     {3,4,2,2,605,624},
     {3,4,2,2,605,624},
     {3,4,2,2,605,624},
     {4,4,2,2,625,649},
     {4,4,2,2,625,649},
     {4,4,2,2,625,649},
     {4,4,2,2,625,649},
     {4,4,2,2,625,649},
     {4,4,2,2,625,649},
     {4,4,2,2,650,674},
     {4,4,2,2,650,674},
     {4,4,2,2,650,674},
     {4,4,2,2,650,674},
     {4,4,2,2,650,674},
     {4,4,2,2,650,674},
     {4,4,2,2,650,674},
     {4,4,2,2,650,674},
     {4,4,2,2,650,674},
     {4,4,2,2,650,674},
     {4,4,2,2,650,674},
     {4,4,2,2,675,699},
     {4,4,2,2,675,699},
     {4,4,2,2,675,699},
     {4,4,2,2,675,699},
     {4,4,2,2,675,699},
     {4,4,2,2,675,699},
     {4,3,2,2,655,674},
     {4,3,2,2,655,674},
     {4,3,2,2,655,674},
     {4,3,2,2,655,674},
     {4,3,2,2,655,674},
     {4,3,2,2,655,674},
     {4,3,2,2,700,719},
     {4,3,2,2,720,739},
     {4,3,2,2,740,759},
     {4,3,2,2,740,759},
     {4,3,2,2,740,759},
     {4,3,2,2,740,759},
     {4,3,2,2,740,759},
     {4,3,2,2,740,759},
     {4,3,2,2,740,759},
     {4,3,2,2,740,759},
     {4,3,2,2,740,759},
     {4,3,2,2,740,759},
     {4,3,2,2,740,759},
     {4,3,2,2,740,759},
     {4,3,2,2,740,759},
     {4,3,2,2,740,759},
     {4,3,2,2,740,759},
     {4,3,2,2,740,759},
     {4,3,2,2,740,759},
     {4,3,2,2,740,759},
     {4,3,2,2,740,759},
     {4,3,2,2,740,759},
     {4,3,2,2,740,759},
     {4,3,2,2,760,779},
     {4,3,2,2,760,779},
     {4,2,2,2,4,18},
     {4,2,2,2,4,18},
     {4,2,2,2,4,18},
     {4,2,2,2,4,18},
     {4,2,2,2,4,18},
     {4,3,2,2,780,799},
     {4,3,2,2,780,799},
     {4,3,2,2,800,819},
     {4,3,2,2,800,819},
     {4,3,2,2,800,819},
     {4,3,2,2,800,819},
     {4,3,2,2,800,819},
     {4,3,2,2,800,819},
     {4,3,2,2,800,819},
     {4,3,2,2,800,819},
     {4,3,2,2,800,819},
     {4,3,2,2,800,819},
     {4,3,2,2,800,819},
     {4,3,2,2,800,819},
     {4,3,2,2,800,819},
     {4,3,2,2,800,819},
     {4,3,2,2,800,819},
     {4,3,2,2,800,819},
     {4,3,2,2,800,819},
     {4,3,2,2,800,819},
     {4,3,2,2,800,819},
     {4,3,2,2,800,819},
     {4,3,2,2,800,819},
     {4,3,2,2,349,368},
     {4,3,2,2,329,348},
     {4,3,2,2,309,328},
     {4,3,2,2,309,328},
     {4,3,2,2,309,328},
     {4,3,2,2,309,328},
     {4,3,2,2,309,328},
     {4,3,2,2,309,328},
     {4,4,2,2,820,844},
     {4,4,2,2,820,844},
     {4,4,2,2,820,844},
     {4,4,2,2,820,844},
     {4,4,2,2,820,844},
     {4,4,2,2,820,844},
     {4,4,2,2,845,869},
     {4,4,2,2,845,869},
     {4,4,2,2,845,869},
     {4,4,2,2,845,869},
     {4,4,2,2,845,869},
     {4,4,2,2,845,869},
     {4,4,2,2,845,869},
     {4,4,2,2,845,869},
     {4,4,2,2,845,869},
     {4,4,2,2,845,869},
     {4,4,2,2,845,869},
     {4,4,2,2,870,894},
     {4,4,2,2,870,894},
     {4,4,2,2,870,894},
     {4,4,2,2,870,894},
     {4,4,2,2,870,894},
     {4,4,2,2,870,894},
     {3,4,1,2,895,914},
     {3,4,1,2,895,914},
     {3,4,1,2,895,914},
     {3,4,1,2,895,914},
     {3,4,1,2,895,914},
     {3,4,1,2,895,914},
     {3,4,1,2,915,934},
     {3,4,1,2,935,954},
     {3,4,1,2,955,974},
     {3,4,1,2,955,974},
     {3,4,1,2,955,974},
     {3,4,1,2,955,974},
     {3,4,1,2,955,974},
     {3,4,1,2,955,974},
     {3,4,1,2,955,974},
     {3,4,1,2,955,974},
     {3,4,1,2,955,974},
     {3,4,1,2,955,974},
     {3,4,1,2,955,974},
     {3,4,1,2,955,974},
     {3,4,1,2,955,974},
     {3,4,1,2,955,974},
     {3,4,1,2,955,974},
     {3,4,1,2,955,974},
     {3,4,1,2,955,974},
     {3,4,1,2,955,974},
     {3,4,1,2,955,974},
     {3,4,1,2,955,974},
     {3,4,1,2,955,974},
     {3,4,1,2,975,994},
     {3,4,1,2,975,994},
     {2,4,0,2,0,14},
     {2,4,0,2,0,14}};
 
 
char Liste_rotations_robot[995]={1,1,0,1,1,1,1,1,1,1,
     1,1,1,1,0,1,1,1,0,0,
     1,1,1,0,1,1,1,0,1,1,
     1,0,1,1,0,1,1,1,0,1,
     1,1,1,0,1,1,1,0,1,1,
     1,0,1,1,0,1,1,1,0,1,
     1,1,1,1,1,1,1,0,1,1,
     1,0,1,1,0,1,1,1,0,1,
     1,1,1,1,1,1,1,0,1,1,
     1,0,0,1,0,1,1,1,0,1,
     1,1,1,1,1,1,1,0,1,1,
     1,0,0,1,1,1,1,1,1,0,
     0,1,1,1,1,0,1,1,1,1,
     0,0,1,1,1,0,0,0,1,1,
     1,1,1,1,0,1,1,1,1,1,
     0,1,1,1,1,0,0,1,1,1,
     0,0,0,1,1,1,1,1,1,0,
     1,1,1,1,1,0,1,1,1,1,
     0,0,1,1,1,0,0,0,0,1,
     0,1,1,1,0,1,1,1,1,1,
     0,1,1,1,1,0,0,1,1,1,
     0,1,1,1,0,1,1,1,1,1,
     1,1,1,1,1,0,0,1,1,1,
     0,1,1,1,0,1,1,1,1,1,
     1,1,1,1,1,0,0,0,1,1,
     0,1,1,1,0,1,1,1,1,1,
     1,1,1,1,1,0,0,0,0,1,
     0,1,1,1,0,1,1,1,1,1,
     1,1,1,1,1,1,0,0,0,0,
     0,1,1,1,0,1,1,1,1,1,
     1,1,1,1,1,1,1,0,0,0,
     0,1,1,1,0,1,1,1,1,1,
     1,1,1,1,1,1,1,1,0,0,
     0,1,1,1,0,1,1,1,1,1,
     1,1,1,1,0,1,1,1,0,0,
     0,1,1,1,1,1,1,1,1,1,
     1,1,1,1,0,1,1,1,0,0,
     0,1,1,1,1,1,1,1,1,1,
     1,1,1,1,0,1,1,1,0,0,
     1,0,0,0,0,0,1,1,1,1,
     1,1,1,1,1,1,1,1,1,0,
     1,1,1,0,0,1,1,0,0,0,
     0,1,1,1,1,1,1,1,1,0,
     1,1,1,1,0,1,1,1,0,0,
     1,1,0,0,0,0,1,1,1,1,
     1,1,1,1,1,1,1,1,1,1,
     0,1,1,0,0,0,1,1,1,1,
     1,1,1,1,1,1,1,1,1,1,
     0,0,1,0,0,0,1,1,1,1,
     1,1,1,1,1,1,1,1,1,1,
     0,0,1,1,0,0,1,1,1,1,
     1,1,1,1,1,1,0,1,1,1,
     0,0,1,1,0,0,1,1,1,1,
     1,1,0,1,1,1,0,1,1,1,
     0,0,1,1,0,0,1,1,0,1,
     1,1,0,1,1,1,0,1,1,1,
     0,0,1,1,1,0,1,1,0,1,
     1,1,0,1,1,1,0,1,1,1,
     1,0,1,1,1,0,1,0,0,1,
     1,1,0,1,1,1,1,1,1,1,
     1,0,1,1,1,1,1,0,0,1,
     1,1,0,1,1,1,1,1,1,1,
     1,0,1,1,1,1,1,0,0,0,
     1,1,1,0,0,1,1,1,1,0,
     1,1,1,1,0,0,1,1,1,1,
     1,1,0,0,0,1,1,1,0,0,
     1,1,1,1,0,1,1,1,1,1,
     0,1,1,1,1,1,0,0,0,0,
     1,1,1,0,0,1,1,1,1,0,
     1,1,1,1,1,0,1,1,1,1,
     1,1,1,0,0,1,1,1,1,0,
     1,1,1,1,1,0,1,1,1,0,
     1,1,1,0,0,1,1,1,1,1,
     1,1,1,1,1,0,1,1,1,0,
     1,1,0,0,0,1,1,1,1,1,
     1,1,1,1,1,0,1,1,1,0,
     1,0,0,0,0,1,1,1,1,1,
     1,1,1,1,1,0,1,1,1,0,
     0,0,0,0,1,1,1,1,1,1,
     1,1,1,1,1,0,1,1,1,0,
     0,0,0,1,1,1,1,1,1,1,
     1,1,1,1,1,0,1,1,1,0,
     0,0,0,0,1,0,0,1,1,1,
     0,1,1,1,1,1,1,1,1,1,
     1,1,1,1,0,0,0,0,1,1,
     0,0,1,1,1,0,1,1,1,1,
     1,1,1,1,1,1,1,1,1,0,
     0,0,0,1,1,0,0,1,1,1,
     0,1,1,1,1,0,1,1,1,1,
     1,1,1,1,0,0,0,1,1,0,
     1,1,1,1,1,1,1,1,1,1,
     1,1,1,1,0,0,0,1,0,0,
     1,1,1,1,1,1,1,1,1,1,
     1,1,1,1,0,0,1,1,0,0,
     1,1,1,1,1,1,1,1,1,1,
     1,1,1,1,0,0,1,1,0,0,
     1,1,1,0,1,1,1,1,1,1,
     1,1,1,1,0,0,1,1,0,0,
     1,1,1,0,1,1,1,0,1,1,
     1,1,1,1,0};

