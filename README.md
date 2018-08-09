# fate

Probably going to turn into some satellite tracker or something

I have most of the TLE parsing and the SGP algorithm implemented. I "verified" with lizard-tail as I was not able to come up with the same test values as the SpaceTrack #3 report said I should have come up with, but there's really only one way to know for sure: implement ECI to geodosic conversion and check with real-life.

Currently a WIP project.

# Credits

Built with [CLion](https://www.jetbrains.com/clion/)

# References

  - [SpaceTrack Report #3](https://www.celestrak.com/NORAD/documentation/spacetrk.pdf)
  - [Lizard-Tail for verification](http://www.lizard-tail.com/isana/tle/analysis.html)
  - [Revisiting SpaceTrack Report #3](http://ww.celestrak.com/publications/AIAA/2006-6753/AIAA-2006-6753.pdf)
  - [SpaceTrack orbital 3LE sets](https://www.space-track.org/#/tle)
  - [Orbital Coordinate Systems II](https://www.celestrak.com/columns/v02n02/)
  - [Orbital Coordinate Systems III](https://www.celestrak.com/columns/v02n03/)