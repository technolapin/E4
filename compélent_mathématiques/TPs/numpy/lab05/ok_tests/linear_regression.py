test = {
  'name': 'linear_regression',
  'points': 1,
  'suites': [
    {
      'cases': [
        {
          'code': r"""
          >>> np.linalg.norm(w - w_bar) < 1e-4
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
