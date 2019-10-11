test = {
  'name': 'convex_multi',
  'points': 2,
  'suites': [
    {
      'cases': [
        {
          'code': r"""
          >>> cost_fun([-1,-1]), cost_fun([0,0]), cost_fun([1,1])
          (12.5, 2.5000000000000004, 26.5)
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
