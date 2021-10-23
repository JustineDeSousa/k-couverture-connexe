clear
clc
close all

## Nom de l'instance
instance = 'captANOR150_7_4'
instance = 'grille1010_1'

cibles = lecture_instance( instance, 1 );
hold on
affichage_instance( cibles );
affichage_solution( instance, cibles );

hold off