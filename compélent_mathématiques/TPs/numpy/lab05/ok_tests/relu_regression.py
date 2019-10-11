test = {
  'name': 'relu_regression',
  'points': 1,
  'suites': [
    {
      'cases': [
        {
          'code': r"""
          >>> relu_mse_cost(w) < 0.05
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
