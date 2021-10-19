function affichage_solution( instanceName, cibles )
    folder = 'solutions';
    filename = [folder, '/', instanceName, '.sol']
    capteurs = find( importdata(filename," ") );
    
    scatter( cibles(capteurs,2), cibles(capteurs,3), 'filled', 'DisplayName', 'Capteurs');
    scatter( 0, 0, 'filled', 'DisplayName', 'Puit');
    set (gca, "xaxislocation", "top");
    axis('ij')
    grid minor
    legend;
endfunction
