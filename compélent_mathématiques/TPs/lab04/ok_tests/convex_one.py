test = {
  'name': 'convex_one',
  'points': 2,
  'suites': [
    {
      'cases': [
        {
          'code': r"""
          >>> cost_fun(-1), cost_fun(0), cost_fun(1)
          (-0.16, 0.0, 0.24)
          """,
          'hidden': False,
          'locked': False
        },
        {
          'code': r"""
          >>> error < 1e-5
          True
          """,
          'hidden': False,
          'locked': False
        }
      ],
      'scored': True,
      'setup': '',
      'teardown': '',
      'type': 'doctest'
    }
  ]
}
