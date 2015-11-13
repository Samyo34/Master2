% Nom de l’image que l’on va charger 

NomGenerique = 'Arbre' ; 

NomGenerique2 = 'Turtle' ; 

%%NomGenerique = 'Dracula' ; 

%%NomGenerique = 'Rock' ; 

%%NomGenerique = 'Stereo' ; 

% et son suffixe 

Suffixe1 = '.tif' ; 

Suffixe2 = '.jpg' ; 

% Composition des noms des images a charger et chargement de ces images  

Nom1 = sprintf('%sG%s',NomGenerique2,Suffixe1) ;
ImageGauche = double(imread(Nom1)) ;
figure(1) ;
hold off ;
image(uint8(ImageGauche)) ;
hold on ;
axis image ;
title('Image gauche') ;
colormap(gray(256)) ;
drawnow ;   

Nom2 = sprintf('%sD%s',NomGenerique2,Suffixe1) ;
ImageDroite = double(imread(Nom2)) ;
figure(2) ;
hold off ;
image(uint8(ImageDroite)) ;
hold on ;
axis image ;
title('Image droite') ;
colormap(gray(256)) ;
drawnow ;    

[Nlin, Ncol, Nplan] = size(ImageGauche) ;   

% Nombre de points que l’on va sélectionner sur les images 

NombreDePoints = 16 ; 

PointDroite = ones(NombreDePoints,3) ; 

PointGauche = ones(NombreDePoints,3) ; 



% x == colonnes // y == lignes 
a = ones(8,8);

for n=1:8
    figure(1) ;
    drawnow ;
    [x,y] = ginput(1) ;
    plot(x,y,'bo') ;
    PointGauche(n,1:2) = [x,y] ;
    figure(2) ;
    drawnow ;
    [x,y] = ginput(1) ;
    plot(x,y,'ro') ; 
    PointDroite(n,1:2) = [x,y] ;
    a(n,1) = PointGauche(n,1)*PointDroite(n,1);
    a(n,2) = PointGauche(n,1)*PointDroite(n,2);
    a(n,3) = PointGauche(n,1);
    a(n,4) = PointGauche(n,2)*PointDroite(n,1);
    a(n,5) = PointGauche(n,2)*PointDroite(n,2);
    a(n,6) = PointGauche(n,2);
    a(n,7) = PointDroite(n,1);
    a(n,8) = PointDroite(n,2);
end

theta = 0.5;
%%LD = [-150,300,150];
b = ones(8,1);
b(1,1) = PointGauche(1,1);
b(2,1) = PointGauche(1,2);
LDT = a*b;
LD = LDT.';

y_min = 0;
y_max = 461;
x_min = 0;
x_max =267;

if ( ( theta <= pi/2 ) && ( theta >= -pi/2 ) ) || ( ( theta >= 3*pi/2 ) && ( theta <= -3*pi/2 ) )
    y_min = ( -LD(3) - ( LD(1) * x_min ) ) / LD(2) ;
    y_max = ( -LD(3) - ( LD(1) * x_max ) ) / LD(2) ;
else
    x_min = ( -LD(3) - ( LD(2) * y_min ) ) / LD(1) ;
    x_max = ( -LD(3) - ( LD(2) * y_max ) ) / LD(1) ;
end
figure(2) ;
line( [x_min,x_max] , [y_min,y_max] , 'color', 'r' ) ;
drawnow ;