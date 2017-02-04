u = 0.5cm;

randomseed := 435;

def drawLog(expr l) =
    %draw((x, y)--(x + 1, y)--(x + 1, y + l)--(x, y + l)--cycle) scaled u;
    pickup pencircle;
    path p;
    p = (x, y)--(x, y + l){up}..(x + 0.5, y + l + 0.25)..(x + 1, y + l){down}--(x + 1, y);
    draw p scaled u;
    if f = 1 :
        draw((x, y)..(x + 0.5, y + 0.25)..(x + 1, y)..(x + 0.5, y - 0.25)..cycle) scaled u;
        pickup pencircle scaled .5;
        draw((x + 0.25, y)..(x + 0.5, y + 0.125)..(x + 0.75, y)..(x + 0.5, y - 0.125)..cycle) scaled u;
    fi;

    n := 4;    
    for i := 1 upto n :
      xx := x + i / (n + 1);
      pickup pencircle scaled .5;
      pair a, b;
      b := p intersectionpoint ((xx, 0)--(xx, 1000));
      a := b shifted (0, -l);

      b := b shifted (0, -0.1);
      a := a shifted (0, 0.1);

      draw(a--b) scaled u;      
    endfor;

    y := y + l;
    f := 0;
enddef;

def nextRow =
    x := x + 1;
    y := 0;
    f := 1;
enddef;

beginfig(1)
    x := 0;    
    y := 0;

    h := 5;
    hh := 1;
    f := 1;

    pickup pencircle;
    draw((0,-hh)--(0,h+hh)) scaled u;

    drawLog(3);drawLog(2);nextRow;
    drawLog(2);drawLog(3);nextRow;
    drawLog(2);drawLog(3);nextRow;
    y := -0.5; drawLog(3);drawLog(3);nextRow;
    y := -0.5; drawLog(2);drawLog(2);drawLog(2);nextRow;
    drawLog(3);drawLog(2);nextRow;
    y := -0.5; drawLog(2);drawLog(2);drawLog(2);nextRow;

    pickup pencircle;
    draw((x,-hh)--(x,h+hh)) scaled u;
endfig;

end