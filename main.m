clear
clc
close all

## Nom de l'instance
instance = 'captANOR150_7_4'

cibles = lecture_instance( instance );
hold on
affichage_instance( cibles );
affichage_solution( instance, cibles );

hold off