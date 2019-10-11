test = {
  'name': 'tanh_regression',
  'points': 1,
  'suites': [
    {
      'cases': [
        {
          'code': r"""
          >>> tanh_mse_cost(w) < 0.09
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
