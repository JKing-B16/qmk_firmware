// Reduce this number to improve render speed, increase for better print
$fn=100;


w=20;
h=50;
h2=10;
b=12;
bh=3;
brh=4;
br=0.5;
bo=5;

difference(){
    cylinder(h+h2,w/2,w/2);
    union() {
        translate([0,b/2+w/2-bh,h/2])
        cube([b,b,h],true);

        translate([0,0,h+h2])
        rotate([20,0,0])
        cube([w,w+3,h2],true);

        translate([0,w/2-brh,(h+h2)/2])
        cube([w/3,brh,h+h2],true);

        for(k=[0,1,2,3]) {
            translate([b/4,w/2-brh,b*k+br*2+bo/2])
            cube([b/2,brh+bh,br*2],true);
            translate([-b/4,w/2-brh,b*k+br*2+bo/2+bo])
            cube([b/2,brh+bh,br*2],true);

            translate([0,0,b/2+k*b])
            for(i=[-1,1]) {
                for(j=[-1,1]){
                    rotate([90,0,0])
                    translate([i*(b+br)/2,bo/2*j,-w/2])
                    cylinder(bh+brh,br,br);
                }
            }
        }
     }
}


