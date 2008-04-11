/******************** (C) COPYRIGHT 2008 UTC E=M6 ******************************
* File Name          : PathFinding.c
* Author             : UTC E=M6 Team
* Date First Issued  : 05/02/08 : Version 1.0
* Description        : PathFinding fonctions.
********************************************************************************/

#include "def_pathfinding.h"
#include "pathfinding.h"

/* Principe :
- input : 
		position du robot (depart) en mm
		position à atteindre (dest) en mm
		position du robot adverse en mm ( 0,0 = pas d'adverse pris en compte)

- output :
		liste de points à atteindre
*/


void Init_PathFinding(void)
{

	load_robot_adverse(); // on initialise la matrice du robot adverse

	// On charge les coéficients
    Coef_PF_Distance = 4;
    Coef_PF_Temps = 2;
    Coef_PF_Cross = 10;
    
    Coef_PF_Reservoir = 500;
    Coef_PF_Adverse = 500;
    
    Coef_PF_Seuil_Droite = 20;
	Adverse_State = ADVERSE_OUBLIER;
}

u16 Calcul_Score_terrain(u16 case_x, u16 case_y, u16 rotation)
{
    s16 px=0, py=0,j;
    s16 case_xd;
    s16 case_yd;
    s16 Score;
	s16 value;
	//s16 dx, dy;
    //LCD_Debug_String("Score terrain");
    Score = 0;
	
	px=0;
	py=0;

	for(j=Mat_definition_rotation[rotation][INDICE_DEBUT_ROT];j<=Mat_definition_rotation[rotation][INDICE_FIN_ROT];j++)
	{
		value = Liste_rotations_robot[j];

		if (value == 1)
		{
			case_xd = case_x - Mat_definition_rotation[rotation][DX] + px;
            case_yd = case_y - Mat_definition_rotation[rotation][DY] + py;

			if ( (case_xd >= 0) && (case_xd <= 29) && (case_yd >= 0) && (case_yd <= 20) )
			{
                Score = Score + Mat_PF_Terrain[case_xd][case_yd];
			}
            else
			{
                Score = Score + SCORE_OUT;
            }
        }

		px++;
		if(px>Mat_definition_rotation[rotation][DIMX])
		{
			px=0;
			py++;
		}

	}

    return Score;
}

u16 Calcul_poids_case(s16 case_x, s16 case_y, u16 new_temps, u16 rot, u16 px, u16 py)
{
    s32 distance, dx, dy;
    s16 score_terrain;
    s16 dx1, dx2, dy1, dy2;
    s16 cross;
    s16 Malus_Nouveau_passage;

	//LCD_Debug_String("Calcul poids");
    
    dx1 = case_x - Case_Destination.X;
    dy1 = case_y - Case_Destination.Y;
    dx2 = Mat_PF_Case[px][py].Depart_droite.X - Case_Destination.X;
    dy2 = Mat_PF_Case[px][py].Depart_droite.Y - Case_Destination.Y;
    cross = Abs_u32(dx1 * dy2 - dx2 * dy1);
    
    
    if (cross > Coef_PF_Seuil_Droite)
	{
        Mat_PF_Case[case_x][case_y].Depart_droite.X = case_x;
        Mat_PF_Case[case_x][case_y].Depart_droite.Y = case_y;
        Malus_Nouveau_passage = 100;
    }
	else
	{
        Mat_PF_Case[case_x][case_y].Depart_droite.X = Mat_PF_Case[px][py].Depart_droite.X;
        Mat_PF_Case[case_x][case_y].Depart_droite.Y = Mat_PF_Case[px][py].Depart_droite.Y;
        Malus_Nouveau_passage = 0;
	}
   

    if ( (case_x >= 0) && (case_x <= 29) && (case_y >= 0) && (case_y <= 20) )
	{
        dx = Abs_u32(Case_Destination.X - case_x);
        dy = Abs_u32(Case_Destination.Y - case_y);
        distance = (dx * dx + dy * dy) * Coef_PF_Distance;
        
        score_terrain = Calcul_Score_terrain(case_x, case_y, rot);
        
        return  (distance + score_terrain + cross * Coef_PF_Cross + new_temps * Coef_PF_Temps + Malus_Nouveau_passage);
    }
	else
	{
        return  (SCORE_OUT);
    }
	
}


void Calculer_Score_Case(CaseXY case_eval, u16 new_temps, u16 rot, CaseXY case_parent)
{

	int score_temp;
    
	//LCD_Debug_String("Calcul Score");
	
	if ( (case_eval.X >= 0) && (case_eval.X <= 29) && (case_eval.Y >= 0) && (case_eval.Y <= 20) )
	{
		if ( Mat_PF_Case [case_eval.X][case_eval.Y].Score == 0)
		{
			score_temp = Calcul_poids_case(case_eval.X, case_eval.Y, new_temps, rot, case_parent.X, case_parent.Y);

			//LCD_Debug_String("Fin Poids");

			Mat_PF_Case[case_eval.X][case_eval.Y].Score = score_temp;
            Mat_PF_Case[case_eval.X][case_eval.Y].Parent = case_parent;
            Mat_PF_Case[case_eval.X][case_eval.Y].Temps = new_temps;
            Liste_PF_Ouvert[Nb_Noeuds_Ouverts] = case_eval;
            Nb_Noeuds_Ouverts = Nb_Noeuds_Ouverts + 1;  
        }
    }
}
void Evaluer_voisins(CaseXY case_eval)
{
    CaseXY delta_case;
    //Dim angle_case_destination As Integer
    //Dim i_angle As Integer, i_angle_div As Integer
    int parent_temps;
    //Dim reste_x As Integer, reste_y As Integer
    //LCD_Debug_String("Evaluer voisins");
    
    
	parent_temps = Mat_PF_Case[case_eval.X][case_eval.Y].Temps;
    

			delta_case.X = case_eval.X + 1;
            delta_case.Y = case_eval.Y + 0;
            Calculer_Score_Case (delta_case, (parent_temps + 5 * Coef_PF_Temps), 0, case_eval);
            
            delta_case.X = case_eval.X + 0;
            delta_case.Y = case_eval.Y + 1;
            Calculer_Score_Case (delta_case, (parent_temps + 5 * Coef_PF_Temps), 90, case_eval);
                        
            delta_case.X = case_eval.X - 1;
            delta_case.Y = case_eval.Y + 0;
            Calculer_Score_Case (delta_case, (parent_temps + 5 * Coef_PF_Temps), 180, case_eval);
                        
            delta_case.X = case_eval.X + 0;
            delta_case.Y = case_eval.Y - 1;
            Calculer_Score_Case (delta_case, (parent_temps + 5 * Coef_PF_Temps), 270, case_eval);
}

void Start_PathFinding(void)
{
    int i, j, case_xd, case_yd;

	for (i = 0; i < 30; i++) // On reinitialise les tableaux du score et du terrain
    {
	    for (j = 0 ; j < 21 ; j++)
		{
            Mat_PF_Case[i][j].Score = 0;
            Mat_PF_Terrain[i][j] = 0;
		}
	}
    
    //On place le robot adverse dans la matrice utilisé dans le PathFinding :
    
	if(Adverse_State == ADVERSE_PRESENT)
	{
	    for (i = 0 ; i < Adverse_Dim.X ; i++)
		{
	        for (j = 0 ; j < Adverse_Dim.Y ; j++)
			{
	            case_xd = Case_Adverse.X + i - Adverse_Centre.X;
	            case_yd = Case_Adverse.Y + j - Adverse_Centre.Y;
	            if ( (Adverse_MAT[i][j] == 1) &&(case_xd >= 0) && (case_xd <= 29) && (case_yd >= 0) && (case_yd <= 20) )
	                Mat_PF_Terrain[case_xd][case_yd] = Coef_PF_Adverse;
		        }
	    }
	}
    
    // On place les reservoirs sur le terrain
    Mat_PF_Terrain[29][7] = Coef_PF_Reservoir;
    Mat_PF_Terrain[22][0] = Coef_PF_Reservoir;
    Mat_PF_Terrain[23][0] = Coef_PF_Reservoir;
    Mat_PF_Terrain[6][0] = Coef_PF_Reservoir;
    Mat_PF_Terrain[7][0] = Coef_PF_Reservoir;
    Mat_PF_Terrain[0][7] = Coef_PF_Reservoir;

    // On commence avec 1 case anciennement ouverte : la case de départ
}


void PathFinding(CaseXY Point_Depart, CaseXY Point_Destination, CaseXY Point_Adverse, ListePoints * ListePassage)
{
	int securite;
    CaseXY best_case;
	

    securite = 0;
	
	// Converstion des postions(cm) en case(1 case = 10x10cm)
	Case_Depart.X = Point_Depart.X / 10;
	Case_Depart.Y = Point_Depart.Y / 10;

	Case_Destination.X = Point_Destination.X / 10;
	Case_Destination.Y = Point_Destination.Y / 10;

	Case_Adverse.X = Point_Adverse.X / 10;
	Case_Adverse.Y = Point_Adverse.Y / 10;


    Start_PathFinding(); // Réinitialiser les tableaux
    
	// Initialisation du PathFinding avec le point de départ
    Nb_Noeuds_Ouverts = 1;
    Liste_PF_Ouvert[0].X = Case_Depart.X;
    Liste_PF_Ouvert[0].Y = Case_Depart.Y;
    Mat_PF_Case[Case_Depart.X][Case_Depart.Y].Score = 10000;
    Mat_PF_Case[Case_Depart.X][Case_Depart.Y].Temps = 0;
    Mat_PF_Case[Case_Depart.X][Case_Depart.Y].Depart_droite = Case_Depart;
	best_case.X = Case_Depart.X; // on commence à la case de départ
    best_case.Y = Case_Depart.Y;
    
    do
	{
        //Si la meilleur case est la destionation, on quitte (trajet trouvé)
        if ( (best_case.X == Case_Destination.X) && (best_case.Y == Case_Destination.Y) )
            Fin_PF = 1;
        else // sinon, on continue de chercher le trajet en partant des voisins
        {
			Evaluer_voisins (best_case);
            //On met a jour la liste des noeuds ouverts, et on cherche la nouvelle meilleure case
            //on donne le noeud à fermer. On récupère le nouveau meilleur noeud
            best_case = MAJ_PathFinding(best_case);
        }
        securite = securite + 1;
		if( (Mat_PF_Case[best_case.X][best_case.Y].Score>SCORE_CIBLE_INACCESSIBLE) && (securite>NB_MOUVEMENT_MIN) )
			securite = NB_MOUVEMENT_MAX; // On quitte le PathFinding car point non accessible
    }
    while ( (!Fin_PF) && (securite < NB_MOUVEMENT_MAX) ); // Fin_PF est global (bouton d'arret sur Fe_vue)

	if(Fin_PF)
	{ // On a trouvé un chemin
		Chemin(ListePassage);
		ListePassage->Points[ListePassage->TailleListe-1]=Point_Destination; // On remplace la destination par ses coordonnées exactes
	}
	else
	{
		//cout<<endl<<"Pas de trajet trouvé"<<endl;
		ListePassage->TailleListe = 0; // Pas de chemin trouvé
	}
}

CaseXY MAJ_PathFinding(CaseXY case_a_fermer)
{
// Fait 2 choses :
//	- Enlève la case explorée de la frontière
//	- Trouve la case frontière avec le score le + faible
	CaseXY best_case;
    int best_score = 100000, i, decaler = 0, temp_score, indice_max;
     
    // on initialise avec le premier noeud
	// (best_score=10000)
    
	indice_max= (Nb_Noeuds_Ouverts - 2) ; // On ferme toujours un noeud (-1 -1)

    for (i = 0 ; i <= indice_max ; i++)
    {    
        // Fermer le noeud anciennement utilisé pour ses voisins
        // revient à enlever un point de la liste des noeuds ouverts
        if ( (Liste_PF_Ouvert[i].X == case_a_fermer.X) && (Liste_PF_Ouvert[i].Y == case_a_fermer.Y) && (decaler == 0) )
        {
		    decaler = 1;
            Nb_Noeuds_Ouverts = Nb_Noeuds_Ouverts - 1 ;
		}
		if (decaler == 1) // On décale si le flag décaler=1
           Liste_PF_Ouvert[i] = Liste_PF_Ouvert[(i + 1)];
    
        // On recherche la meilleur case parmis les noeuds ouverts
        temp_score = Mat_PF_Case[Liste_PF_Ouvert[i].X][Liste_PF_Ouvert[i].Y].Score;
        if (temp_score < best_score)
		{
            best_score = temp_score;
            best_case.X = Liste_PF_Ouvert[i].X;
            best_case.Y = Liste_PF_Ouvert[i].Y;
        }
        
    }
        
    return best_case;
}

void Chemin(ListePoints * ListePassage)
{
    int securite=0;
    int case_xx, case_yy;
    int px, py;
	ListePoints Liste_Points_Passage_avant_simplification;

    // on part de la destination
    case_xx = Case_Destination.X;
    case_yy = Case_Destination.Y;
    Liste_Points_Passage_avant_simplification.Points[0].X = case_xx; // La destination
	Liste_Points_Passage_avant_simplification.Points[0].Y = case_yy;
    Liste_Points_Passage_avant_simplification.TailleListe = 1;
    
    do
	{   
        if ( (Mat_PF_Case[case_xx][case_yy].Depart_droite.X == case_xx) && (Mat_PF_Case[case_xx][case_yy].Depart_droite.Y == case_yy) )
        {
            Liste_Points_Passage_avant_simplification.Points[Liste_Points_Passage_avant_simplification.TailleListe].X = case_xx;
            Liste_Points_Passage_avant_simplification.Points[Liste_Points_Passage_avant_simplification.TailleListe].Y = case_yy;
            Liste_Points_Passage_avant_simplification.TailleListe ++;
		}
        
        // on repart avec le parent
        px = Mat_PF_Case[case_xx][case_yy].Parent.X;
        py = Mat_PF_Case[case_xx][case_yy].Parent.Y;
        
        case_xx = px;
        case_yy = py;
        
        securite = securite + 1;
    } while ( (securite < 100) && (!((case_xx == Case_Depart.X)&&(case_yy == Case_Depart.Y))) );
    
    Liste_Points_Passage_avant_simplification.Points[Liste_Points_Passage_avant_simplification.TailleListe].X = case_xx; // Le départ
    Liste_Points_Passage_avant_simplification.Points[Liste_Points_Passage_avant_simplification.TailleListe].Y = case_yy;

    if (Liste_Points_Passage_avant_simplification.TailleListe >= 2) // si il y a plus de 2 points, on peut simplifier 
	{
		//cout<<endl<<"Simplification possible ("<<Liste_Points_Passage_avant_simplification.TailleListe<<" points)"<<endl;
        Simplifier_Chemin( &Liste_Points_Passage_avant_simplification, ListePassage);
	}
	else
	{
		//cout<<endl<<"Trajet Direct vers destination"<<endl;
		ListePassage->TailleListe=1;
		// Trajet direct vers la desination
		// On mettra les coordonnées exactes de la destination dans PathFinding(..) (en cm)
	}
}

void Simplifier_Chemin(ListePoints * Points_Passage_avant_simplification, ListePoints * Points_Passage){
/*
 [fin , , , , , , , depart]

 Le but est d'enlever les points inutiles dans le chemin
 exemple : Les x et O sont des points de passage. Il faut enlever les 'O'

                  x
                 /
                /
   x---O---O---x
*/

    int i_cour;
    int i_dest;
	int i_milieu;
    int dx1, dx2, dy1, dy2;
    int cross;
    int secu = 0, cross_seuil;

    Points_Passage->TailleListe = 0;
    
    i_cour = Points_Passage_avant_simplification->TailleListe;
    i_milieu = i_cour - 1;
    i_dest = i_cour - 2;
	cross_seuil = Coef_PF_Seuil_Droite / 2;
	if(cross_seuil<10)
		cross_seuil = 10;

    do
	{
			
			dx1 = Points_Passage_avant_simplification->Points[i_milieu].X - Points_Passage_avant_simplification->Points[i_dest].X;
            dy1 = Points_Passage_avant_simplification->Points[i_milieu].Y - Points_Passage_avant_simplification->Points[i_dest].Y;
            dx2 = Points_Passage_avant_simplification->Points[i_cour].X - Points_Passage_avant_simplification->Points[i_dest].X;
            dy2 = Points_Passage_avant_simplification->Points[i_cour].Y - Points_Passage_avant_simplification->Points[i_dest].Y;
			cross = Abs_u32(dx1 * dy2 - dx2 * dy1);
			//cout<<cross<<" : "<<dx1<<" , "<<dy1<<" , "<<dx2<<" , "<<dy2<<endl;
			
            if (cross < cross_seuil) //cross_seuil)
			{
				
                //Remplir_Case_Terrain Liste_Points_Passage_avant_simplification(i_milieu).X, Liste_Points_Passage_avant_simplification(i_milieu).Y, RGB(128, 128, 0)
                i_dest = i_dest - 1;
                i_milieu = i_milieu - 1;
			}
            else
			{
				Points_Passage->Points[Points_Passage->TailleListe].X = Points_Passage_avant_simplification->Points[i_milieu].X * 10 - 5;
                Points_Passage->Points[Points_Passage->TailleListe].Y = Points_Passage_avant_simplification->Points[i_milieu].Y * 10 - 5;
                Points_Passage->TailleListe++;
                i_cour = i_milieu;
                i_milieu = i_cour - 1;
                i_dest = i_cour - 2;
            }
    secu = secu + 1;
    } while ( (i_cour >= 2) && (i_dest >= 0) && (secu < 10) ); 

}


void load_robot_adverse(void)
{

    Adverse_Dim.X = 5;
    Adverse_Dim.Y = 5;
    
    Adverse_Centre.X = 2;
    Adverse_Centre.Y = 2;
    
    
    Adverse_MAT[0][0] = 0;
    Adverse_MAT[1][0] = 1;
    Adverse_MAT[2][0] = 1;
    Adverse_MAT[3][0] = 1;
    Adverse_MAT[4][0] = 0;
    Adverse_MAT[0][1] = 1;
    Adverse_MAT[1][1] = 1;
    Adverse_MAT[2][1] = 1;
    Adverse_MAT[3][1] = 1;
    Adverse_MAT[4][1] = 1;
    Adverse_MAT[0][2] = 1;
    Adverse_MAT[1][2] = 1;
    Adverse_MAT[2][2] = 1;
    Adverse_MAT[3][2] = 1;
    Adverse_MAT[4][2] = 1;
    Adverse_MAT[0][3] = 1;
    Adverse_MAT[1][3] = 1;
    Adverse_MAT[2][3] = 1;
    Adverse_MAT[3][3] = 1;
    Adverse_MAT[4][3] = 1;
    Adverse_MAT[0][4] = 0;
    Adverse_MAT[1][4] = 1;
    Adverse_MAT[2][4] = 1;
    Adverse_MAT[3][4] = 1;
    Adverse_MAT[4][4] = 0;
}


/*

u32 Abs_u32(s32 val)
{
	if(val<0)
		return -val;
	return val;
}
*/

/* End of file pathfinding.c*/
