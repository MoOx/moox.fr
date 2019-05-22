open ReactNative;

let scrollYAnimatedValue = Animated.Value.create(0.);
let requested = ref(false);

if (Consts.isClient) {
  // loop on each scroll event throttled with requestAnimationFrame

  open Webapi.Dom;
  let tick = _ => {
    scrollYAnimatedValue
    ->Animated.spring(
        Animated.Value.Spring.config(
          ~toValue=window->Window.scrollY->Animated.Value.Spring.fromRawValue,
          (),
        ),
      )
    ->Animated.start();
  };
  window
  |> Window.addEventListener("scroll", _ =>
       if (! requested^) {
         requested := true;
         ReactNative.AnimationFrame.request(() => {
           tick();
           requested := false;
         })
         ->ignore;
       }
     );
};

[@react.component]
let make = (~children) => {
  <>
    <AppMeta />
    <WindowSizeFilter.MMin> <HeaderLargeWithRouter /> </WindowSizeFilter.MMin>
    <View> children </View>
    <WindowSizeFilter.MMin> <Footer /> </WindowSizeFilter.MMin>
    <WindowSizeFilter.SMax>
      <div className="BlurView FixedBottom">
        <TabBarWithRouter links=Consts.menuLinks />
      </div>
      <TabBar.Placeholder />
    </WindowSizeFilter.SMax>
  </>;
};
