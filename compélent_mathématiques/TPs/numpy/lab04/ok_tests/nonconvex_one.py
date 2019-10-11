test = {
  'name': 'nonconvex_one',
  'points': 2,
  'suites': [
    {
      'cases': [
        {
          'code': r"""
          >>> cost_fun(-1), cost_fun(0), cost_fun(1)
          (0.7403023058681397, 0.5403023058681398, -0.7899924966004455)
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
