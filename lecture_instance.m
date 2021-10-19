function cibles = lecture_instance( instanceName )
    folder = 'instances';
    filename = [folder, '/', instanceName, '.dat'] 
    cibles = importdata(filename," ");
end



