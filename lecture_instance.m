function cibles = lecture_instance( instanceName, mode )
    folder = 'instances';
    filename = [folder, '/', instanceName, '.dat'] 
    if ( mode == 0 ) #alea
        cibles = importdata(filename," ");
    else if( mode == 1) #truncatedGrid
         cibles= importdata(filename," ",2);
    endif
    
end



