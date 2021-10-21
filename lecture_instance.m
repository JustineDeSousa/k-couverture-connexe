function cibles = lecture_instance( instanceName, mode )
    folder = 'instances';
    filename = [folder, '/', instanceName, '.dat'] 
    if ( mode == 0 ) #alea
        cibles = importdata(filename," ");
    else if( mode == 1) #truncatedGrid
        A = importdata(filename," ",2)
        A.data(1)
    endif
    
end



