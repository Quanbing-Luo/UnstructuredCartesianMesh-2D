clear;
model = createpde();
geometryFromEdges(model,@circleg);

figure(1) 
pdegplot(model,'EdgeLabels','on'); 
axis equal

hmax = 0.2;%´ÖÍø¸ñ
%hmax = 0.1;%´ÖÍø¸ñ
%hmax = 0.05;% Ï¸Íø¸ñ
%hmax = 0.03;% ¸üÏ¸Íø¸ñ
generateMesh(model,'Hmax',hmax,'GeometricOrder','linear');
figure(2)
pdemesh(model); 
axis equal

[p,e,t] = meshToPet(model.Mesh);
e(5,:)=1;

fid = fopen('./Data/mesh.txt','w');
fprintf(fid,'Points\r\n');
fprintf(fid,'%i \r\n',size(p,2));
fprintf(fid,'%i %e %e \r\n', [1:size(p,2);p]);

fprintf(fid,'Triangles\r\n');
fprintf(fid,'%i\r\n',size(t,2));
fprintf(fid,'%i %i %i %i \r\n', [1:size(t,2); t(1:3,:)-1]); 

fprintf(fid,'Edges\r\n');
fprintf(fid,'%i \r\n',size(e,2));
fprintf(fid,'%i %i %i %i \r\n', ...
    [1:size(e,2) ;e(1,:)-1; e(2,:)-1 ; e(5,:)]); 

fclose(fid);



