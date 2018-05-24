open Helpers;

open BsReactNative;

let styles =
  StyleSheet.create(
    Style.(
      {
        "block": style([flex(1.), flexDirection(Row)]),
        "imageContainer": style([overflow(Hidden)]),
        "image":
          style([
            position(Absolute),
            top(Pt(0.)),
            bottom(Pt(0.)),
            right(Pt(0.)),
            left(Pt(0.)),
          ]),
        "row": style([flexDirection(Row), justifyContent(SpaceBetween)]),
        "text":
          style([
            flexDirection(Row),
            flex(1.),
            padding(Pt(20.)),
            alignItems(FlexStart),
            lineHeight(28.),
            color("#030303"),
          ]),
        "bullet": style([]),
        "title": style([fontSize(Float(22.))]),
      }
    ),
  );

let component = ReasonReact.statelessComponent("TalkPreview");

let make = (~item: Types.partialContentItem, _) => {
  ...component,
  render: _self => {
    let href = "/talk/" ++ item##id ++ "/";
    <View key=item##id style=styles##block>
      <Text style=styles##text>
        <Text style=styles##bullet> ({j|•|j} |> text) </Text>
        <Spacer small=true />
        <UnderlinedTextLink style=styles##title href>
          (item##title |> text)
          <small>
            (
              switch (Js.Undefined.toOption(item##conference)) {
              | None => nothing
              | Some(conference) =>
                <Text> (" @ " ++ conference |> text) </Text>
              }
            )
          </small>
        </UnderlinedTextLink>
        <Spacer small=true />
        (
          switch (Js.Undefined.toOption(item##lang)) {
          | None => nothing
          | Some(lang) => <Text> ("[" ++ lang ++ "] " |> text) </Text>
          }
        )
      </Text>
    </View>;
  },
};
