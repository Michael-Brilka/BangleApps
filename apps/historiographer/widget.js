let startwidget = false;
let batteryState = 0;
let storageState = 0;

let reload= function(){
    WIDGETS["widhistorio"].draw();
};

WIDGETS["widhistorio"]={
  area:"tl", // tl (top left), tr (top right), bl (bottom left), br (bottom right), be aware that not all apps support widgets at the bottom of the screen
  width: 29+13+23, // how wide is the widget? You can change this and call Bangle.drawWidgets() to re-layout
  draw:function() {
  if (!startwidget) return;
                          g.drawImage(atob("ExPC////AABZOgAAAAFVVVQABVVVUAAUAAFCqpAABaqqgAAWqqqAAFKqqoABQqqqQAUCqqlAFAKqhUBQABQFQUAAUAUFAAFAABQABQAAUAVVVUFAFVVVBQBQABQUAVVVVVABVVVVAA=="),this.x+1,this.y+2);
    if(batteryState == 1)
      g.drawImage(atob("DRPC////AACA/wAAAVQAAFUABVVVAVVVQFAAUBQAFAUABQFAAUBQAEAUAAIFAACBQACgVUCoFVCqpVQqqVUAqFVAKBVUCAAAAgA="), this.x+24, this.y+2);

    if(batteryState == 2)
      g.drawImage(atob("DRPC////gP/k6AAAAqgAAKoACqqqAqqqgKAAoCgAKAoACgKAAoCgAIAoAAEKAABCgABQqoBUKqBVWqgVVqoAVKqAFCqoBAAAAQA="), this.x+24, this.y+2);

    if(storageState == 1) g.drawImage(atob("EhLB/wAA//8AAcAAM/+EgDAgDggDwgDw//w//w/Pw+Hw8Dw8Dw+Hw/Pw//wAAAAAAA=="), this.x+27+13, this.y+2);

    if(storageState == 2) g.drawImage(atob("EhLB/+To//8AAcAAM/+EgDAgDggDwgDw//w//w/Pw+Hw8Dw8Dw+Hw/Pw//wAAAAAAA=="), this.x+27+13, this.y+2);

},
  setActive:function(){
    startwidget = true;
    reload();
  },
  reload:function() {
    reload();
    Bangle.drawWidgets(); // relayout all widgets
  },
  reset:function(){
    startwidget = false;
    batteryState = 0;
    storageState = 0;
    reload();
    Bangle.drawWidgets();
  },
  setBatteryState:function(state){
    if(state > batteryState)
    {
      batteryState = state;
      reload();
    }
  },
  setStorageState:function(state){
    if(state > storageState)
    {
      storageState = state;
      reload();
    }
  }
};
reload();
